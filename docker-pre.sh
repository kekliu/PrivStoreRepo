#!/bin/bash

echo "APT::Acquire::Retries \"3\";" > /etc/apt/apt.conf.d/80-retries

apt update
apt upgrade -y
rm -rf /var/lib/apt/lists/*
