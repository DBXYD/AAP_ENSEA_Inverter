ENSEA - Projet Onduleur Triphasé didactique, 48V, 10A

# Présentation du projet

# Guide d'utilisation

# FAQ

# Pannes courantes 
## Dysfonctionnement des Mosfet
Plusieurs causes peuvent causer la destruction des transistors : 
* Non respect des temps mort,
* Commande provocant une freinage trop important : retour du courant chargeant les condensateurs sur le bus d'alimentation. Ceci provoque la montée en tension du bus au-delà des spécifications des transistor de puissance

Détection de la panne : 
* Débrancher l'ensemble des câbles de la maquette, et le cas échéant, attendre que les condensateurs du bus d'alimentation soient totalement vides.
* A l'aide d'un multimètre, en mode diode, tester la continuité entre :
  - Entre la sortie U et le bus d'alimentation (Q202)
  - Entre la sortie U et la masse (Q203)
  - Entre la sortie V et le bus d'alimentation (Q302)
  - Entre la sortie V et la masse (Q303)
  - Entre la sortie W et le bus d'alimentation (Q402)
  - Entre la sortie W et la masse (Q403)
* Le fonctionnement normal est l'absence de continuité électrique. Dans le cas d'une continuité, le transistor en question est HS, il doit donc être changé.

# Composants
* Drivers de Mosfet/optocoupleur : HCPL-315J, Optocoupleurs sortie logique 0.5A IGBT Gate Drive [link](https://www.mouser.fr/ProductDetail/Broadcom-Avago/HCPL-315J?qs=s%252BgfxR24RQ4lntGToXJAvA%3D%3D)
* Transistor MOSFET : IRF540NPBF, MOSFET de puissance, Canal N, 100 V, 33 A, 0.044 ohm, TO-220AB, Traversant [Link](https://fr.farnell.com/infineon/irf540npbf/transistor-mosfet-canal-n-to220/dp/8648298?st=irf540n)
* Capteur de Courant : GO 10-SME/SP3, Capteur de courant, 300 kHz, SOIC, 8 Broche(s), 3.135 V, 3.465 V [Link](https://fr.farnell.com/lem/go-10-sme-sp3/capteur-courant-300khz-soic-8/dp/3796461?st=GO%2010-SME/SP3)
* Power supply : MP-LD30-23B15R2 - Alimentation montage PCB AC/DC (PSU), ITE, Équipements Ménagers et Transformateurs, 1 sortie [link](https://fr.farnell.com/multicomp-pro/mp-ld30-23b15r2/power-supply-ac-dc-15v-2a/dp/3780527)
* Power regulator : Input : 5V DC, Output : 3.3V DC, AZ1117CH-3.3TRG1 - LDO, FIXE, 3,3V, 0.8A, -20 A 125°C [link](https://fr.farnell.com/diodes-inc/az1117ch-3-3trg1/ldo-fixe-3-3v-0-8a-20-a-125-c/dp/3483073RL)
* Alimentation 15V/400mA isolé : MPRB2415S-6W - Conv. DC/DC, montage traversant isolé, ITE, 4:1, 6 W, 1 sortie, 15 V, 400 mA [link](https://fr.farnell.com/multicomp-pro/mprb2415s-6w/convertisseur-dc-dc-15v-0-4a/dp/3652723)
* Alimentation 5V/200mA isolé : 17791063215 - MagI³C-VISM Variable Isolated SIP Module, [Link](https://www.we-online.com/components/products/datasheet/17791063215.pdf)
* Connector : PX0580/PC Connecteur de puissance IEC, Entrée IEC C14, 10 A, 250 VAC, Traversant [link](https://fr.farnell.com/bulgin/px0580-pc/embase-iec-c14-carte-proto-10a/dp/313853)
* Screen : MDOB128064XV-YI - OLED graphique, 128 x 64 pixels, Jaune sur noir, 3.3V, I2C, 35.5mm x 32mm, -40 °C [Link](https://fr.farnell.com/midas/mdob128064xv-yi/afficheur-oled-cob-128-x-64-pix/dp/3407293)
* Break resistor : 162-3488 - Résistance à montage sur châssis Aluminium, 5Ω 100W ±1% [Link](https://fr.rs-online.com/web/p/resistances-a-montage-sur-chassis/1623488)
* Break schottky : VS-15TQ060S-M3 - Redresseur Schottky, 60 V, 15 A, Une, TO-263AB, 3 Broche(s), 620 mV [Link](https://fr.farnell.com/vishay/vs-15tq060s-m3/diode-schottky-simple-60v-to263ab/dp/2909608?ost=2909608)
