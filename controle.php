<?php

 //variavel para receber o valor
 
$valor=$_GET['valor'];  


//$name = 'arquivo.txt';


//condicao 
if($valor==0){  
	$file=fopen("arquivo.txt","w");
	fwrite($file,0);             //escreve
	fclose($file);               //fecha a comunicaçao
	echo '<meta http-equiv="refresh" content="0;URL=../index.html">'; 
}	

if($valor==1){
	$file=fopen("arquivo.txt","w");
	fwrite($file,1);             //escreve
	fclose($file);       
	echo '<meta http-equiv="refresh" content="0;URL=../index.html">'; 
}

?>
