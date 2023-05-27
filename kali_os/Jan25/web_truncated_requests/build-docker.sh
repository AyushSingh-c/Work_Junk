#!/bin/bash
docker build -t web_truncated_requests .
docker run --name=web_truncated_requests --rm -p1337:1337 -it web_truncated_requests
