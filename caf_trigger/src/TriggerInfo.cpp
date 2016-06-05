//////////////////////////////////////////////////////////
// This is trigeff_proc/src/MyTriggerInfo.cpp
// moved to the emcertify namespace.
/////////////////////////////////////////////////////////

#include <cstdio>
#include "caf_trigger/TriggerMap.hpp"

namespace caf_trigger {

  // This function returns the 

  int global_CMTversionX100(TriggerMap *runnum_to_triggerversion, int run){

    int triggerversion = runnum_to_triggerversion->TriggerX100(run);
    int lastrun = runnum_to_triggerversion->LastRun();

    if ( run > lastrun ) {
      printf("caf_trigger::TriggerInfo ERROR:\n");
      printf("Current Run number exceeds the last run in caf_trigger/parameters/runvstriglistX100.txt !\n");
      printf("Run number: %d, Last Run: %d\nConsider a manual fix by running caf_trigger/parameters/mkruntrigvlist.py\n\n", run, lastrun);
      exit(1);
    }

    if ( triggerversion <= 0 ) {
      printf("caf_trigger::TriggerInfo ERROR:\n");
      printf("Unable to find trigger version for runno %d !\n",run);
      printf("Is caf_trigger/parameters/runvstriglistX100.txt up-to-date ?\n\n");
      exit(1);
    }

    /*
    if(run < 150000 || run > 246067){
      printf("That run number (%d) is out of the range of this method: 150000 < run number < 246067. [TriggerInfo.hpp]\n", run) ;
      return 0;
    }
    */
    //run is in the range [150000,246067]
  
    // break it up into groups of 1000 runs, then work from there
    int divide1000 = (int) (run/1000);
    switch (divide1000){    

    case 150: // run = 150###
      return 501;
      
    case 151: // run = 151###
      return 501;
      
    case 152: // run = 152###
      return 501;
      
    case 153: // run = 153###
      if(run<153312) return 510;
      if(run<153342) return 501;
      if(run<153789) return 510;
      if(run<153975) return 700;
      return 510;
      
    case 154: // run = 154###
      if(run<154494) return 510;
      if(run<154565) return 710;
      return 720;
      
    case 155: // run = 155###
      if(run<155465) return 720;
      return 730;
      
    case 156: // run = 156###
      return 730;     
      
    case 157: // run = 157###
      if(run<157595) return 730;
      return 731;
      
    case 158: // run = 158###
      if(run<158465) return 731;
      return 740;
      
    case 159: // run = 159###
      return 740;
      
      
    case 160: // run = 160###
      return 800;
      
    case 161: // run = 161###
      if(run<161101) return 800;
      if(run<161110) return 810; //don't need 'else' because it would have returned already
      if(run<161299) return 800;
      if(run<161616) return 810;
      if(run<161621) return 800;
      return 810;

    case 162: // run = 162###
      if(run<162458) return 810;
      return 820;

    case 163: // run = 163###
      return 820;

    case 164: // run = 164###
      if(run<164380) return 820;
      return 830;

    case 165: // run = 165###
      if(run<165635) return 830;
      if(run<165973) return 840;
      return 841;

    case 166: // run = 166###
      return 841;
    
    case 167: // run = 167###
      if(run<167019) return 841;
      return 920;
    
    case 168: // run = 168###
      if(run<168028) return 920;
      if(run<168029) return 930;
      if(run<168132) return 920;
      if(run<168414) return 930;
      if(run<168415) return 920;
      if(run<168870) return 930;
      return 931;
    case 169: // run = 169###
      if(run<169512) return 931;
      if(run<169513) return 950;
      if(run<169524) return 931;
      return 950;
    case 170: // run = 170###
      if(run<179175) return 950;
      if(run<170176) return 1000;
      if(run<170247) return 950;
      return 1000;
    
    case 171: // run = 171###
      if(run<171885) return 1000;
      return 1001;
    
    case 172: // run = 172###
      if(run<172500) return 1001;
      if(run<172708) return 1002;
      return 1003;
    case 173: // run = 173###
      if(run<173352) return 1003;
      if(run<173531) return 1030;
      return 1035;

    case 174: // run = 174###
      if(run<174241) return 1035;
      if(run<174242) return 1036;
      if(run<174681) return 1035;
      if(run<174682) return 1036;
      if(run<174806) return 1035;
      if(run<174807) return 1036;
      if(run<174845) return 1035;
      return 1100;

    case 175: // run = 175###
      if(run<175027) return 1100;
      if(run<175626) return 1102;
      return 1103;
    
    case 176: // run = 176###
      if(run<176869) return 1103;
      return 1104;
    
    case 177: // run = 177###
      if(run<177284) return 1104;
      if(run<177286) return 1200; //this was actually global_CMT_test-12.00
      if(run<177313) return 1104;
      if(run<177315) return 1200; //this was actually global_CMT_test-12.00
      if(run<177688) return 1104;
      if(run<177691) return 1201; //this was actually global_CMT_test-12.01
      return 1104;
    
    case 178: // run = 178###
      if(run<178019) return 1104;
      if(run<178021) return 1202; //this was actually global_CMT_test-12.02
      if(run<178069) return 1104;
      if(run<178071) return 1210;
      if(run<178097) return 1104;
      if(run<178104) return 1210;
      if(run<178618) return 1104;
      if(run<178620) return 1210;
      if(run<178722) return 1104;
      if(run<178992) return 1210;
      return 1220;

    case 179: // run = 179###
      return 1220;

    case 180: // run = 180###
      if(run<180625) return 1220;
      if(run<180915) return 1230;
      if(run<180916) return 1231;
      return 1230;

    case 181: // run = 181###
      return 1230;
    
    case 182: // run = 182###
      return 1230;
    
    case 183: // run = 183###
      return 1230;
    
    case 184: // run = 184###
      if(run<184951) return 1230;
      return 1231;
    
    case 185: // run = 185###
      if(run<185422) return 1231;
      return 1232;
    
    case 186: // run = 186###
      return 1232;

    case 187: // run = 187###
      if(run<187830) return 1232;    
      if(run<187831) return 1231;
      return 1232;

    case 188: // run = 188###
      if(run<188954) return 1232;
      return 1233;
    
    case 189: // run = 189###
      if(run<189047) return 1233;
      return 1234;

    case 190: // run = 190###
      if(run<190219) return 1234;
      if(run<190329) return 1235;
      if(run<190382) return 1236;
      return 1237;
    
    case 191: // run = 191###
      return 1237;
    
    case 192: // run = 192###
      return 1237;
    
    case 193: // run = 193###
      return 1237;
    
    case 194: // run = 194###
      if(run<194200) return 1237;
      if(run<194256) return 1302;
      if(run<194264) return 1237;
      if(run<194269) return 1302;
      if(run<194449) return 1237;
      if(run<194452) return 1302;
      if(run<194567) return 1237;
      if(run<194595) return 1303;
      if(run<194662) return 1237;
      if(run<194724) return 1303;
      if(run<194725) return 1304;
      return 1303;
    
    case 195: // run = 195###
      if(run<195229) return 1303;
      if(run<195351) return 1310;
      if(run<195839) return 1311;
      return 1320;

    case 196: // run = 196###
      if(run<196414) return 1320;
      return 1321;
    
    case 197: // run = 197###
      return 1321;
    
    case 198: // run = 198###
      return 1321;
    
    case 199: // run = 199###
      return 1321;
    
    case 200: // run = 200###
      return 1321;
    
    case 201: // run = 201###
      if(run<201534) return 1321;
      if(run<201679) return 1322;
      if(run<201680) return 1321;
      return 1322;

    case 202: // run = 202###
      if(run<202019) return 1322;
      if(run<202025) return 1323;
      if(run<202106) return 1330;
      if(run<202108) return 1331;
      if(run<202797) return 1330;
      if(run<202959) return 1331;
      if(run<202961) return 1303;
      if(run<202964) return 1321;
      if(run<202965) return 1331;
      if(run<202988) return 1332;
      return 1340;
    
    case 203: // run = 203###
      if(run<203375) return 1340;
      if(run<203623) return 1350;
      if(run<203624) return 1351;
      if(run<203839) return 1350;
      return 1351;
    
    case 204: // run = 204###
      if(run<204299) return 1351;
      if(run<204684) return 1352;
      if(run<204686) return 1360;
      if(run<204687) return 1352;
      if(run<204801) return 1361;
      return 1362;

    case 205: // run = 205###
      if(run<205021) return 1362;
      if(run<205380) return 1370;
      return 1380;
    
    case 206: // run = 206###
      if(run<206597) return 1380;
      if(run<206937) return 1381;
      return 1390;

    case 207: // run = 207###
      if(run<207217) return 1390;
      if(run<207223) return 1400;
      if(run<207279) return 1390;
      if(run<207280) return 1400;
      if(run<207343) return 1390;
      if(run<207346) return 1400;
      if(run<207719) return 1390;
      if(run<207749) return 1410;
      return 1390;
    
    case 208: // run = 208###
      if(run<208167) return 1390;
      if(run<208246) return 1420;
      if(run<208247) return 1390;
      if(run<208444) return 1420;
      if(run<208501) return 1390;
      if(run<208719) return 1421;
      if(run<208720) return 1430;
      if(run<208728) return 1421;
      if(run<208800) return 1430;
      if(run<208819) return 1431;
      if(run<208820) return 1430;
      return 1431;

    case 209: // run = 209###
      if(run<209100) return 1431;
      if(run<209105) return 1390;
      if(run<209785) return 1431;
      return 1440;

    case 210: // run = 210###
      if(run<210177) return 1440;
      if(run<210268) return 1441;
      if(run<210338) return 1442;
      if(run<210442) return 1443;
      if(run<210690) return 1450;
      if(run<210747) return 1451;
      if(run<210985) return 1460;
      if(run<210986) return 1461;
      if(run<210988) return 1460;
      return 1461;

    case 211: // run = 211###
      if(run<211047) return 1461;
      if(run<211049) return 1460;
      if(run<211059) return 1461;
      if(run<211060) return 1460;
      if(run<211093) return 1461;
      if(run<211094) return 1460;
      if(run<211153) return 1461;
      if(run<211198) return 1470;
      if(run<211199) return 1460;
      if(run<211271) return 1470;
      if(run<211290) return 1471;
      if(run<211513) return 1470;
      if(run<211909) return 1480;
      if(run<211910) return 1481;
      if(run<211926) return 1480;
      return 1481;

    case 212: // run = 212###
      if(run<212126) return 1481;
      if(run<212343) return 1490;
      if(run<212804) return 1481;
      return 1482;

    case 213:
      if(run<213073) return 1482;
      if(run<213125) return 1490;
      if(run<213127) return 1481;
      if(run<213154) return 1490;
      if(run<213155) return 1481;
      if(run<213820) return 1490;
      if(run<213821) return 1482;
      return 1490;
      
    case 214:
      return 1490;

    case 215:
      if(run<215054) return 1490;
      if(run<215083) return 1492;
      if(run<215084) return 1490;
      if(run<215289) return 1492;
      return 1493;
      
      //the next cases added by Olav Sept 17th
    case 216:
      return 1494;
      
    case 217:
      return 1495;
      
    case 218:
      return 1496;

    case 219:
      return 1497;

    case 220:
      return 1498;

    case 221:
      if(run<221993) return 1499;
      return 1500;
      
    case 222:
      if(run<222240) return 1500;
      if(run<222272) return 1501;
      if(run<222582) return 1502;
      if(run<222709) return 1503;
      if(run<222905) return 1504;
      return 1505;
      
    case 223:
      if(run<223025) return 1505;
      if(run<223162) return 1506;
      if(run<223342) return 1507;
      if(run<223620) return 1508;
      if(run<223636) return 1509;
      if(run<223652) return 1510;
      return 1511;
      
    case 224:
      if(run<224006) return 1511;
      if(run<224290) return 1512;
      return 1513;
      
    case 225:
      if(run<225300) return 1513;
      if(run<225427) return 1514;
      if(run<225554) return 1515;
      if(run<225822) return 1516;
      return 1517;
      
    case 226:
      if(run<226120) return 1520;
      if(run<226972) return 1521;
      return 1522;
      
    case 227:
      return 1522;
      
    case 228:
      if(run<228112) return 1522;
      if(run<228929) return 1523;
      return 1524;
      
    case 229:
      if(run<229007) return 1524;
      if(run<229394) return 1525;
      if(run<229522) return 1526;
      if(run<229716) return 1527;
      if(run<229795) return 1528;
      return 1529;
      
    case 230:
      if(run<230067) return 1529;
      if(run<230126) return 1530;
      if(run<230528) return 1550;
      return 1551;
      
    case 231:
      if(run<231035) return 1551;
      if(run<231632) return 1552;
      if(run<231862) return 1553;
      if(run<231956) return 1554;
      return 1560;
      
    case 232:
      if(run<232152) return 1561;
      if(run<232447) return 1562;
      if(run<232869) return 1563;
      if(run<232871) return 1562;
      return 1563;
      
    case 233:
      if(run<233118) return 1563;
      if(run<233395) return 1564;
      if(run<233396) return 1563;
      if(run<233450) return 1564;
			if(run<233477) return 1565;
			return 1566;

		case 234 :
			if(run<234027) return 1566 ;
			if(run<234207) return 1567 ;
			if(run<234309) return 1568 ;
			if(run<234348) return 1569 ;
			if(run<234514) return 1570 ;
			if(run<234638) return 1571 ;
			if(run<234693) return 1572 ;
			if(run<234860) return 1573 ;
			return 1580 ;
    case 235:
      return 1580;
    case 236:
      return 1580;
    case 237:
      if(run<237080) return 1580;
      else if(run<237403) return 1590;
      else return 1591;
    case 238:
      if(run<238295) return 1591;
      else return 1592;
		case 239:
      return 1592;
    case 240:
      if(run<240222) return 1592;
      else if(run<240390) return 1593;
			else if(run<240393) return 1600;
			else if(run<240439) return 1593;
			else if(run<240567) return 1600;
			else if(run<240666) return 1594;
			else if(run<240718) return 1595;
			else if(run<240744) return 1596;
			else if(run<240832) return 1601;
			else if(run<240853) return 1602;
			else if(run<240953) return 1603;
			else return 1604;
		case 241:
			if(run<241507) return 1604;
			else if(run<241890) return 1605;
			else return 1606;
		case 242:
			return 1606;
		case 243:	
			return 1606;
		case 244:
			if(run<244123) return 1606;
			else if(run<244158) return 1608;
			else if(run<244159) return 1607;
			else return 1608;
		case 245:
			if(run<245920) return 1608;
			else return 1609;
		case 246:
			if(run<246068) return 1609;
			else return 1610;

    default: 
        return triggerversion;

     // this sould never happen since run is in [150000,246067]
     // printf("divide1000 (%d = (int) run number (%d) / 1000) is not in range [150,246]. [TriggerInfo.cpp]\n", divide1000, run);
     // return 0;
    }

    printf("ERROR: passed switch statement. [Caf_trigger::TriggerInfo.cpp]\n");
    return 0;

  }
}  
