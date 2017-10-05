<?php

if ($_SERVER['REQUEST_URI'] == '/time/')
{
	if ($_SERVER['REQUEST_METHOD'] == 'PUT')
	{
		$data = file_get_contents('php://input');
		$json = json_decode($data, true);
		if (!isset($json['time']) || !is_string($json['time']))
		{
			exit(1);
		}
		$t = DateTime::createFromFormat(DateTime::ISO8601, $json['time']);
		if (!$t)
		{
			exit(1);
		}
		file_put_contents('time.db', $t->getTimestamp());
	}
	else if ($_SERVER['REQUEST_METHOD'] == 'GET')
	{
		$time = DateTime::createFromFormat('U', intval(@file_get_contents('time.db')));
		echo json_encode(array("time" =>  $time->format('c')));
	}
	exit(0);
}

readfile('get.html');
