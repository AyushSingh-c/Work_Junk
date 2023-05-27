#!/bin/bash
docker rm -f web_vax_register
docker build -t web_vax_register . 
docker run --name=web_vax_register --rm -p1337:1337 -it web_vax_register
