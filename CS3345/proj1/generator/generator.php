<?php


$fileContent = file("dictionary.txt");



$max = count($fileContent) - 1;

$usedArray = [];



$outputFile = "input4.txt";

$file = fopen($outputFile,"a");

$iterations = 69420;



$i = 0;
while($i < $iterations){
	$type = mt_rand(1,6);
	
	
	if($type == 1){
		$randIndex = mt_rand(0,$max);
		$word = explode("/", $fileContent[$randIndex])[0];
		$word = strtolower($word);
		$word = preg_replace('/\s/', '', $word);
		fwrite($file, "A ".$word."\n");
		array_push($usedArray, $word);
		
	}
	else if($type == 2){
		fwrite($file, "L\n");
	}
	else if($type == 3){
		fwrite($file, "M\n");
	}
	
	else if($type == 4){
		$weight = mt_rand(0, 7);
		if($weight > 4 or count($usedArray) == 0){
			$randIndex = mt_rand(0,$max);
			$word = explode("/", $fileContent[$randIndex])[0];
			$word = strtolower($word);
			$word = preg_replace('/\s/', '', $word);
			fwrite($file, "D ".$word."\n");
		}
		else{
			$randIndex = mt_rand(0, count($usedArray) - 1);
			fwrite($file, "D ".$usedArray[$randIndex]."\n");
		}
	}
	else if($type == 5){
		$weight = mt_rand(0, 7);
		if($weight > 4 or count($usedArray) == 0){
			$randIndex = mt_rand(0,$max);
			$word = explode("/", $fileContent[$randIndex])[0];
			$word = strtolower($word);
			$word = preg_replace('/\s/', '', $word);
			fwrite($file, "S ".$word."\n");
		}
		else{
			$randIndex = mt_rand(0, count($usedArray) - 1);
			fwrite($file, "S ".$usedArray[$randIndex]."\n");
		}
		
	}
	
	else if($type == 6){
		fwrite($file, "T ");
		$maxIndex = mt_rand(9,13);
		for($x = 0; $x < $maxIndex; $x++){
			$weight = mt_rand(0, 7);
			if($weight > 4 or count($usedArray) == 0){
				$randIndex = mt_rand(0,$max);
				$word = explode("/", $fileContent[$randIndex])[0];
				$word = strtolower($word);
				$word = preg_replace('/\s/', '', $word);
				fwrite($file, $word);
			}
			else{
				$randIndex = mt_rand(0, count($usedArray) - 1);
				fwrite($file, $usedArray[$randIndex]);
			}
			
			if($x != ($maxIndex - 1)){
				fwrite($file, " ");
			}
		}
		fwrite($file, "\n");
	}
	$i++;
}


fwrite($file, "E\n");




fclose($file);