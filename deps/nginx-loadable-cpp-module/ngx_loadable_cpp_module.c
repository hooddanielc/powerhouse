#include <dlfcn.h>

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
  ngx_str_t load_cpp_shared_object;
} ngx_http_hoc_loc_conf_t;

typedef char *(*ngx_hoc_interface_init_t)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf, ngx_module_t module);

ngx_module_t ngx_loadable_cpp_module;

static void *ngx_http_hoc_create_loc_conf(ngx_conf_t *cf) {
  ngx_http_hoc_loc_conf_t  *conf;
  conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_hoc_loc_conf_t));

  if (conf == NULL) {
      return NGX_CONF_ERROR;
  }

  return conf;
}

/* The module context. */
static ngx_http_module_t ngx_hoc_ctx = {
  NULL, /* preconfiguration */
  NULL, /* postconfiguration */

  NULL, /* create main configuration */
  NULL, /* init main configuration */

  NULL, /* create server configuration */
  NULL, /* merge server configuration */

  ngx_http_hoc_create_loc_conf, /* create location configuration */
  NULL  /* merge location configuration */
};

static char *ngx_http_hoc_load_shared_object_command(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
  ngx_http_hoc_loc_conf_t *holc = conf;
  ngx_str_t *value;

  if (holc->load_cpp_shared_object.data != NULL) {
    return "is duplicate";
  }

  value = cf->args->elts;

  holc->load_cpp_shared_object = value[1];
  char *file_path = (char *) holc->load_cpp_shared_object.data;

  // Load the dynamic library
  void *ngx_hoc_interface_handle;
  ngx_hoc_interface_handle = dlopen(file_path, RTLD_NOW);

  if (!ngx_hoc_interface_handle) {
    fputs (dlerror(), stderr);
    ngx_conf_log_error(NGX_LOG_ERR, cf, 0, "%s shared library failed to load.", file_path);
    return NGX_CONF_ERROR;
  }

  // Load the init method
  dlerror();
  ngx_hoc_interface_init_t ngx_hoc_interface_init;
  ngx_hoc_interface_init = (ngx_hoc_interface_init_t) dlsym(ngx_hoc_interface_handle, "ngx_hoc_interface_init");

  char *dlsym_error = dlerror();

  if (dlsym_error) {
    ngx_conf_log_error(
      NGX_LOG_ERR,
      cf,
      0,
      "%s ngx_hoc_interface_init failed to link. %s", file_path, dlsym_error
    );

    dlclose(ngx_hoc_interface_handle);
    return NGX_CONF_ERROR;
  }

  return ngx_hoc_interface_init(cf, cmd, conf, ngx_loadable_cpp_module);
}

static ngx_command_t ngx_hoc_commands[] = {
  {
    ngx_string("load_cpp_shared_object"), /* directive */
    NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1, /* location context and takes 1 argument*/
    ngx_http_hoc_load_shared_object_command, /* configuration setup function */
    NGX_HTTP_LOC_CONF_OFFSET, /* No offset. Only one context is supported. */
    0, /* Stored in ngx_http_hoc_loc_conf_t */
    NULL
  },

  ngx_null_command /* command termination */
};

ngx_module_t ngx_loadable_cpp_module = {
  NGX_MODULE_V1,
  &ngx_hoc_ctx, /* module context */
  ngx_hoc_commands, /* module directives */
  NGX_HTTP_MODULE, /* module type */
  NULL, /* init master */
  NULL, /* init module */
  NULL, /* init process */
  NULL, /* init thread */
  NULL, /* exit thread */
  NULL, /* exit process */
  NULL, /* exit master */
  NGX_MODULE_V1_PADDING
};
