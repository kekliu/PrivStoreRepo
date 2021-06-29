# k8s
[toc]

## What is k8s?
todo 
## Install
### Deploy minikube on local
1. Install docker: https://docs.docker.com/engine/install/ubuntu/ ;
2. Install minikube: https://minikube.sigs.k8s.io/docs/start/#what-youll-need
### Create local cluster by minikube
```shell
ln -s $(which minikube) /usr/local/bin/kubectl
minikube start --image-mirror-country cn --nodes 3 --registry-mirror https://880de231.mirror.aliyuncs.com
```

### Local path provisioner
```bash
kubectl apply -f https://raw.githubusercontent.com/rancher/local-path-provisioner/master/deploy/local-path-storage.yaml
kubectl annotate storageclass --overwrite local-path storageclass.kubernetes.io/is-default-class=true
kubectl annotate storageclass --overwrite standard storageclass.kubernetes.io/is-default-class=false
```
