<?php





$totalNodes = mt_rand(1, 1024);

$source = mt_rand(1, $totalNodes);

$numberEdges = mt_rand(1, (intdiv($totalNodes, 2) * ($totalNodes - 1)));

$usedEdges = [];


function isIn($pair, $haystack){
	for($i = 0; $i < count($haystack); $i++){
		if($pair[0] == $haystack[$i][0] and $pair[1] == $haystack[$i][1]){
			return true;
		}
	}
	return false;
}


$outputFile = "input4.txt";

$file = fopen($outputFile,"a");




fwrite($file, $totalNodes." ".$source."\n");

for($x = 0; $x < $numberEdges; $x++){
	$vOne = mt_rand(1, $totalNodes);
	$vTwo = mt_rand
	
}




fclose($file);