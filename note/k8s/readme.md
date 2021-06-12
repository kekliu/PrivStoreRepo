# k8s
## What is k8s?
todo 
## Install
### Deploy minikube on local
1. Install docker: https://docs.docker.com/engine/install/ubuntu/ ;
2. Install minikube: https://minikube.sigs.k8s.io/docs/start/#what-youll-need
### Create local cluster by minikube
```shell
ln -s $(which minikube) /usr/local/bin/kubectl
minikube start --nodes 2 ???
```
