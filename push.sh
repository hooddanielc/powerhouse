TAG=$(date -u +"%Y-%m-%dt%H.%M.%Sz")
docker tag dhoodlum/powerhouse dhoodlum/powerhouse:$TAG
docker push dhoodlum/powerhouse:$TAG
docker push dhoodlum/powerhouse
