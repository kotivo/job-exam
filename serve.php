<?php

if ($_SERVER['REQUEST_URI'] == '/time/')
{
	if ($_SERVER['REQUEST_METHOD'] == 'PUT')
	{
		$data = file_get_contents('php://input');
		$json = json_decode($data, true);
		if (!isset($json['time']))
		{
			exit(1);
		}
		$t = DateTime::createFromFormat(DateTime::ISO8601, $json['time']);
		if (!$t)
		{
			exit(1);
		}
		file_put_contents('database', json_encode($json));
	}
	else if ($_SERVER['REQUEST_METHOD'] == 'GET')
	{
		readfile('database');
	}
	exit(0);
}

readfile('get.html');
