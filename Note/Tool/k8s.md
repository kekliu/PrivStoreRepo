# k8s

[toc]

## Try k8s by minikube

### Install minikube

#### docker-ce

```bash
sudo apt-get update
sudo apt-get -y install apt-transport-https ca-certificates curl gnupg-agent software-properties-common
curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get -y update
sudo apt-get -y install docker-ce
```

#### kubectl

```bash
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl
#cat << EOF > /etc/apt/sources.list.d/kubernetes.list
#deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main
#EOF
#sudo apt update
#sudo apt -y install kubectl
```

#### minikube

```bash
wget https://github.com/kubernetes/minikube/releases/download/v1.17.1/minikube_1.17.1-0_amd64.deb
sudo dpkg -i minikube_1.17.1-0_amd64.deb
minikube start --vm-driver=docker --extra-config=kubelet.cgroup-driver=systemd --image-repository=registry.cn-hangzhou.aliyuncs.com/google_containers --nodes=3
## or use the following to use one node only (much faster)
#sudo minikube start --vm-driver=none --image-repository=registry.cn-hangzhou.aliyuncs.com/google_containers
#sudo cp -r /root/.kube /root/.minikube $HOME
#sudo chown -R $USER $HOME/.kube $HOME/.minikube
```

