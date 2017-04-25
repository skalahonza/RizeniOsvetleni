# 10. Semestrální úloha - vestavný systém s architekturou ARM

## Distribuované řízení osvětlení

Úloha je určená pro dvojice studentů bez rozdílu pro studijní program OI i KyR Úlohu je možné řešit i samostatně, jednotlivci. 
Navrhněte systém pro nastavování intenzity a barvy osvětlení v jednotlivých místnostech domácnosti. 
V každé místnosti je umístěna řídicí jednotka, která řídí intenzitu a barvu stropního osvětlení a osvětlení/barvu stěn. 
Takové řešení může sloužit k dosažení maximálního komfortu a podporu denního režimu obyvatel. 
V mnoha situacích je ale potřeba nastavit osvětlení manuálně. K tomu je každá jednotka vybavena trojicí otočných voličů a grafickým displejem. 
Jednotky jsou propojené komunikační sítí (fyzické médium ETHERNET 1Gbps, protokol TCP/IP) a z každé jednotky by mělo být možné nastavit intenzitu na libovolné jiné. 
Stejně tak je požadovaná možnost sledovat přítomnost a stav ostatních jednotek.
Pro komunikaci se používá protokol UDP (nespojovaná služba). 
Veškeré příkazy i stav se posílají mezi porty 55555. 
Jednotky jednou za sekundu vysílají do celé lokální sítě svůj stav (broadcast). 
Každá jednotka sleduje tyto informace a vytváří si seznam dostupných jednotek a jejich stavu. 
Uživatel pak může voličem vybrat jednotku, sledovat její stav a měnit ho zasláním příkazu vloženého do UDP datagramu a poslaného na jedinečnou cílovou adresu vybrané jednotky. 
Jednotky jsou jednoznačně určené svojí síťovou (IPv4) adresou. 
Kromě adresy jsou pro zvýšení komfortu obsluhy jsou do jednotek zapsaná jména (maximálně 16 znaků) a grafický symbol/ikona o rozměrech 16×16 bodů v barevné hloubce RGB 565 (celková délka 512 byte). Pro veškeré přenosy po síti se používá síťové pořadí jednotlivých byte začínající nejvíce významným bytem (network order = big-endian).