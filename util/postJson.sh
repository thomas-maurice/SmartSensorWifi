#!/bin/bash

serv=localhost:8000

id=1
pass=testpass

curl -X POST -H "Content-Type: application/json" -d \
	'{"id":"'$id'","pass":"'$pass'", "temp":"'128'", "lum":"'17'"}' \
	$serv
