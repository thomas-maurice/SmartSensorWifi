#!/bin/bash

serv=https://smartsensorwifi.plil.net:40098/recup.php

id=1
pass=PaSsWoRd

curl -k -X POST -H "Content-Type: application/json" -d \
	'{"id":"'$id'","password":"'$pass'", "temp":"'128'", "lum":"'17'"}' \
	$serv
