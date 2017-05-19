# Semestrální úloha - vestavný systém s architekturou ARM

## Distribuované řízení osvětlení

<p>
Navrhněte systém pro nastavování intenzity a barvy osvětlení
v jednotlivých místnostech domácnosti. V každé místnosti
je umístěna řídicí jednotka, která řídí intenzitu a barvu
stropního osvětlení a osvětlení/barvu stěn. Takové řešení
může sloužit k dosažení maximálního komfortu a podporu
denního režimu obyvatel. V mnoha situacích je ale potřeba
nastavit osvětlení manuálně. K tomu je každá jednotka
vybavena trojicí otočných voličů a grafickým displejem.
Jednotky jsou propojené komunikační sítí (fyzické médium
ETHERNET 1Gbps, protokol TCP/IP) a z každé jednotky by
mělo být možné nastavit intenzitu na libovolné jiné.
Stejně tak je požadovaná možnost sledovat přítomnost
a stav ostatních jednotek.
</p>

<p>
Pro komunikaci se používá protokol UDP (nespojovaná služba).
Veškeré příkazy i stav se posílají mezi porty 55555.
Jednotky jednou za sekundu vysílají do celé lokální sítě
svůj stav (broadcast). Každá jednotka sleduje tyto informace
a vytváří si seznam dostupných jednotek a jejich stavu.
Uživatel pak může voličem vybrat jednotku, sledovat její
stav a měnit ho zasláním příkazu vloženého do UDP datagramu
a poslaného na jedinečnou cílovou adresu vybrané jednotky.
Jednotky jsou jednoznačně určené svojí síťovou (IPv4) adresou.
Kromě adresy jsou pro zvýšení komfortu obsluhy jsou do jednotek
zapsaná jména (maximálně 16 znaků) a grafický symbol/ikona
o rozměrech 16×16 bodů v barevné hloubce RGB 565
(celková délka 512 byte). Pro veškeré přenosy po síti se
používá síťové pořadí jednotlivých byte začínající
nejvíce významným bytem (network order = big-endian).
</p>

## Formát zpráv
<table class="inline">
	<tbody><tr class="row0">
		<th class="col0"> Byte offset </th><th class="col1"> Datový typ </th><th class="col2 leftalign"> Význam                         </th>
	</tr>
	<tr class="row1">
		<td class="col0 leftalign"> 0 … 3     </td><td class="col1 leftalign"> uint32_t   </td><td class="col2 leftalign"> Kontrolní číslo 'ALC1' (ip adresa zařízení)</td>
	</tr>
	<tr class="row2">
		<td class="col0 leftalign"> 4 … 7     </td><td class="col1 leftalign"> uint32_t   </td><td class="col2"> Verze protokolu 1.0 0x00010000 </td>
	</tr>
	<tr class="row3">
		<td class="col0 leftalign"> 8 … 11    </td><td class="col1 leftalign"> uint32_t   </td><td class="col2"> Typ zprávy (0 status, 1 inkrement, 2 nastavení na hodnotu ) </td>
	</tr>
	<tr class="row4">
		<td class="col0 leftalign"> 12 …      </td><td class="col1 leftalign">            </td><td class="col2 leftalign"> Vlastní data zprávy            </td>
	</tr>
</tbody></table>

## Obsah stavové zprávy
<table class="inline">
	<tbody><tr class="row0">
		<th class="col0"> Byte offset </th><th class="col1 leftalign"> Datový typ    </th><th class="col2 leftalign"> Význam                         </th>
	</tr>
	<tr class="row1">
		<td class="col0 leftalign"> 0 … 3     </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Kontrolní číslo 'ALC1'         </td>
	</tr>
	<tr class="row2">
		<td class="col0 leftalign"> 4 … 7     </td><td class="col1 leftalign"> uint32_t      </td><td class="col2"> Verze protokolu 1.0 0x00010000 </td>
	</tr>
	<tr class="row3">
		<td class="col0 leftalign"> 8 … 11    </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Typ zprávy 0 - status          </td>
	</tr>
	<tr class="row4">
		<td class="col0 leftalign"> 12 … 15   </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Strop RGB 888, nejvyšších 8 bitů nevyužito  </td>
	</tr>
	<tr class="row5">
		<td class="col0 leftalign"> 16 … 19   </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Stěny RGB 888, nejvyšších 8 bitů nevyužito  </td>
	</tr>
	<tr class="row6">
		<td class="col0 leftalign"> 20 … 35   </td><td class="col1 leftalign"> 16x char      </td><td class="col2 leftalign"> textový popis jednotky, nevyužité znaky na konci nastavit na nulu                      </td>
	</tr>
	<tr class="row7">
		<td class="col0 leftalign"> 36 … 547  </td><td class="col1"> 256x uint16_T </td><td class="col2"> grafický symbol reprezentující místnost </td>
	</tr>
</tbody></table>

## Obsah zprávy pro korekci intenzity, typ 1
<table class="inline">
	<tbody><tr class="row0">
		<th class="col0"> Byte offset </th><th class="col1 leftalign"> Datový typ    </th><th class="col2 leftalign"> Význam                          </th>
	</tr>
	<tr class="row1">
		<td class="col0 leftalign"> 0 … 3     </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Kontrolní číslo 'ALC1'          </td>
	</tr>
	<tr class="row2">
		<td class="col0 leftalign"> 4 … 7     </td><td class="col1 leftalign"> uint32_t      </td><td class="col2 leftalign"> Verze protokolu 1.0 0x00010000  </td>
	</tr>
	<tr class="row3">
		<td class="col0 leftalign"> 8 … 11    </td><td class="col1 leftalign"> uint32_t      </td><td class="col2"> Typ zprávy 1 - inkrement/úprava </td>
	</tr>
	<tr class="row4">
		<td class="col0 leftalign"> 12 … 13   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky R pro strop       </td>
	</tr>
	<tr class="row5">
		<td class="col0 leftalign"> 14 … 15   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky G pro strop       </td>
	</tr>
	<tr class="row6">
		<td class="col0 leftalign"> 16 … 17   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky B pro strop       </td>
	</tr>
	<tr class="row7">
		<td class="col0 leftalign"> 18 … 19   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky R pro stěny       </td>
	</tr>
	<tr class="row8">
		<td class="col0 leftalign"> 20 … 21   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky G pro stěny       </td>
	</tr>
	<tr class="row9">
		<td class="col0 leftalign"> 22 … 23   </td><td class="col1 leftalign"> int16_t       </td><td class="col2 leftalign"> Úprava složky B pro stěny       </td>
	</tr>
</tbody></table>

<p>
Zpráva pro nastavení (typ 2) používá stejný formát, jako zpráva pro úpravu. Jednotlivé složky však nejsou inkrementy, ale hodnoty, na které se mají složky nastavit. Záporná hodnota pak značí, že se daná složka nastavovat nemá.
</p>