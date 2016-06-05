#!/D0/ups/perl/Linux-2-4/v5_006_1a/bin/perl

$name="john";

##### number of events #######

if("$name" eq "junjie"){

  $NZ_ALL =7837.91;  $NZ_ALL_e=sqrt($NZ_ALL);
  $NZ_CC  =4285.14;   $NZ_CC_e=sqrt($NZ_CC);
  $NZ_CCEC=2905.36; $NZ_CCEC_e=sqrt($NZ_CCEC);
  $NZ_EC  =668.76;    $NZ_EC_e=sqrt($NZ_EC);

  $NW_ALL=129238;    $NW_ALL_e=sqrt(100810);
  $NW_CC=102397;     $NW_CC_e=sqrt(82621);
  $NW_EC=26841;      $NW_EC_e=sqrt(18189);

}
elsif("$name" eq "john"){
  $NZ_ALL =7739.2;  $NZ_ALL_e=sqrt($NZ_ALL);
  $NZ_CC  =4216.9;     $NZ_CC_e=sqrt($NZ_CC);
  $NZ_CCEC=2885.4;     $NZ_CCEC_e=sqrt($NZ_CCEC);
  $NZ_EC  =636.9;    $NZ_EC_e=sqrt($NZ_EC);

  $NW_ALL=131097.8; $NW_ALL_e=sqrt(0);
  $NW_CC=104301.6;  $NW_CC_e=sqrt(0);
  $NW_EC=26796.2;   $NW_EC_e=sqrt(0);

}
else{ #harald

  $NZ_ALL =7763.06;     $NZ_ALL_e=sqrt($NZ_ALL);
  $NZ_CC  =4271.95;     $NZ_CC_e=sqrt($NZ_CC);
  $NZ_CCEC=2868.2;     $NZ_CCEC_e=sqrt($NZ_CCEC);
  $NZ_EC  =645.005;      $NZ_EC_e=sqrt($NZ_EC);

  $NW_ALL=129140; $NW_ALL_e=sqrt(100451);
  $NW_CC=102693;  $NW_CC_e=sqrt(77700); #bogus error
  $NW_EC=26446.9;   $NW_EC_e=sqrt(20400); #also bogus error

}

##### acceptance values ######
$AZ_ALL=0.186415;
$AZ_CC=0.102943;
$AZ_CCEC=0.070247;
$AZ_EC=0.013225;

$AW_ALL=0.290385;
$AW_CC=0.229254;
$AW_EC=0.0611312;


###### Relative uncertainties #####
$sys_stat_W=0.0133;  $sys_stat_Z=0.0166; $sys_stat_R=0.0109;
$sys_W=0.0168;       $sys_Z=0.0254;      $sys_R=0.0185;
$pdf_W=0.00874;      $pdf_Z=0.00933;     $pdf_R=0.00633;

$sys_stat_W_CC=0.0096;
$sys_stat_W_EC=0.0270;

$sys_stat_Z_CC=0.0183;
$sys_stat_Z_CCEC=0.0220;
$sys_stat_Z_EC=0.0460;
$sys_stat_R_CC=0.0105;
$sys_stat_R_EC=0.0252;

###### LUMI #####
$L=160.5;
$Lre=0.065;

####### Drell-Yan and W backgrounds #####
$FDY=0.0165;
$FZEE=0.0024;
$FWTN=0.01225;


#################### Z #########################
$sZ_ALL= $NZ_ALL * (1-$FDY) / $L / $AZ_ALL;
$sZ_CC = $NZ_CC * (1-$FDY) / $L / $AZ_CC;
$sZ_EC = $NZ_EC * (1-$FDY) / $L / $AZ_EC;
$sZ_CCEC = $NZ_CCEC * (1-$FDY) / $L / $AZ_CCEC;

$Z_ALL_stat=$sZ_ALL * $NZ_ALL_e/$NZ_ALL;
$Z_ALL_sys_stat=$sZ_ALL*$sys_stat_Z;
$Z_ALL_sys=$sZ_ALL*$sys_Z;
$Z_ALL_pdf=$sZ_ALL*$pdf_Z;
$Z_ALL_lumi=$sZ_ALL*$Lre;

$Z_CC_sys_stat=$sZ_CC*$sys_stat_Z_CC;
$Z_CCEC_sys_stat=$sZ_CCEC*$sys_stat_Z_CCEC;
$Z_EC_sys_stat=$sZ_EC*$sys_stat_Z_EC;

$Z_CC_stat=$sZ_CC * $NZ_CC_e/$NZ_CC;
$Z_EC_stat=$sZ_EC * $NZ_EC_e/$NZ_EC;
$Z_CCEC_stat=$sZ_CCEC * $NZ_CCEC_e/$NZ_CCEC;


printf("\$(ALL) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat} \\pm %0.2f_{sys} \\pm %0.2f_{pdf} \\pm %0.2f_{lumi} ~{\\textstyle pb}\$\\\\\n",
       $sZ_ALL,$Z_ALL_stat,$Z_ALL_sys_stat,$Z_ALL_sys,$Z_ALL_pdf,$Z_ALL_lumi);
printf("\$(CCCC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $sZ_CC,$Z_CC_stat,$Z_CC_sys_stat);
printf("\$(CCEC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $sZ_CCEC,$Z_CCEC_stat,$Z_CCEC_sys_stat);
printf("\$(ECEC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $sZ_EC,$Z_EC_stat,$Z_EC_sys_stat);


#################### W #########################
$sW_ALL= $NW_ALL * (1-$FZEE-$FWTN) / $L / $AW_ALL;
$sW_CC= $NW_CC * (1-$FZEE-$FWTN) / $L / $AW_CC;
$sW_EC= $NW_EC * (1-$FZEE-$FWTN) / $L / $AW_EC;

$W_ALL_stat=$sW_ALL * $NW_ALL_e/$NW_ALL;
$W_ALL_sys_stat=$sW_ALL*$sys_stat_W;
$W_ALL_sys=$sW_ALL*$sys_W;
$W_ALL_pdf=$sW_ALL*$pdf_W;
$W_ALL_lumi=$sW_ALL*$Lre;

$W_CC_sys_stat=$sW_CC * $sys_stat_W_CC;
$W_EC_sys_stat=$sW_EC * $sys_stat_W_EC;

$W_CC_stat=$sW_CC * $NW_CC_e/$NW_CC;
$W_EC_stat=$sW_EC * $NW_EC_e/$NW_EC;

printf("\n");
printf("\$(ALL) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat} \\pm %0.2f_{sys} \\pm %0.2f_{pdf} \\pm %0.2f_{lumi} ~{\\textstyle pb}\$\\\\\n",
       $sW_ALL,$W_ALL_stat,$W_ALL_sys_stat,$W_ALL_sys,$W_ALL_pdf,$W_ALL_lumi);
printf("\$(CC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $sW_CC,$W_CC_stat,$W_CC_sys_stat);
printf("\$(EC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $sW_EC,$W_EC_stat,$W_EC_sys_stat);

#################### R #########################
$R_ALL=$sW_ALL / $sZ_ALL;
$R_CC=$sW_CC / $sZ_CC;
$R_EC=$sW_EC / $sZ_EC;

$R_ALL_stat=$R_ALL * sqrt(($W_ALL_stat/$sW_ALL)**2 + ($Z_ALL_stat/$sZ_ALL)**2);
$R_ALL_sys_stat=$R_ALL*$sys_stat_R;
$R_ALL_sys=$R_ALL*$sys_R;
$R_ALL_pdf=$R_ALL*$pdf_R;

$R_CC_sys_stat=$R_CC*$sys_stat_R_CC;
$R_EC_sys_stat=$R_CC*$sys_stat_R_EC;

$R_CC_stat=$R_CC * sqrt(($W_CC_stat/$sW_CC)**2 + ($Z_CC_stat/$sZ_CC)**2);
$R_EC_stat=$R_EC * sqrt(($W_EC_stat/$sW_EC)**2 + ($Z_EC_stat/$sZ_EC)**2);

printf("\n");
printf("\$(ALL) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat} \\pm %0.2f_{sys} \\pm %0.2f_{pdf} ~{\\textstyle pb}\$\\\\\n",
       $R_ALL,$R_ALL_stat,$R_ALL_sys_stat,$R_ALL_sys,$R_ALL_pdf);
printf("\$(CC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $R_CC,$R_CC_stat,$R_CC_sys_stat);
printf("\$(EC) = %0.2f \\pm %0.2f_{stat} \\pm %0.2f_{sys_stat}\$\\\\\n",
       $R_EC,$R_EC_stat,$R_EC_sys_stat);

