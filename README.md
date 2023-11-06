# ENSEA - Projet Onduleur Triphasé didactique, 60V, 10A
- Rédaction : Nicolas Papazoglou, Alexis Martin,
- Desgin et Réalisation : Nicolas Papazoglou, Alexis Martin, Patricia Kittel,
- Conseils : Pierre Toussaint.

# Présentation du projet

## Motivations
Dans le cadre de la formation des étudiants de l'ENSEA, les professeurs ont ressenti le besoin de créer une maquette pédagogique pour plusieurs raisons : 
* De nombreuses pannes récurentes sur les maquettes existantes,
* Réparations chronophages voir impossibles,
* L'ensemble du matériel est caché des étudiants, ils ne peuvent pas voir l'intérieur, le routage de la carte et les composants,
* Le coût de l'ensemble du matériel acheté est important.

## Objectifs
* Réalisation d'une maquette fiable pour les TPs d’électrotechnique et automatique : Gain en temps et en autonomie pour les étudiants,
* Feedback automatique en fonction des erreurs détectées : Gain en autonomie pour les étudiants, possibilité de travail hors séance sans
supervision d’un professeur,
* Projet open-source (disponible sur github),
* Compréhension globale possible par les étudiants, application de l’ensemble de leurs cours dans une maquette,
* Création modulaire, réutilisable dans d’autres cours/projets,
* Evolution possible à d’autres enseignements (buck/boost, 4Q, brushless, moteurs synchrones, asservissement, etc...),
* Maintenance facile et rapide

## Cahier des charges
* Onduleur triphasé 60V / 15A,
* Protections surtensions et surintensités,
* Commande de mise sous tension,
* Pilotage par liaison UART over USB,
* Utilisable en commande “brushless” : entrées position “hall” ,
* Utilisable en commande vectorielle ou MCC : entrée position “encoder”,
* Protection alimentation non réversible : module “freinage”,
* Vérification automatique des temps morts,
* Mesure de courants (hall) dans les 3 phases + entrée,
* Mesure de tension dans les 3 phases + entrée,
* Alimentation externe secteur,
* Affichage erreurs, intensité PWM (affiche externe),
* Sorties mesures de courants et PWMs,
* Boitier,
* Tenue thermique,
* Isolation galvanique.

![synopsis](https://github.com/DBXYD/AAP_ENSEA_Inverter/blob/master/documentation/synopsis/AAP_Inverter-Global.drawio.png)

# Guide d'utilisation


# Guide du développeur
La majorité des signaux sont disponibles sur les connecteurs morpho au format des cartes Nucleo-64.
Sur la base des cartes Nucleo, les connecteurs répérés CN7 et CN10 sont disponibles pour intégrer une carte custom.

### Connecteur CN7
| Type           | Label         | Pin number |    | Label         | Type           |
|----------------|---------------|------------|----|---------------|----------------|
| Digital Output | UART_TX_STM32 | 1          | 2  | UART_RX_STM32 | Digital Input  |
|                | N.C.          | 3          | 4  | NRST_STM32    | Digital Output |
|                | N.C.          | 5          | 6  | 5V            | Power Input    |
|                | N.C.          | 7          | 8  | GND           | Power Input    |
|                | N.C.          | 9          | 10 | N.C           |                |
|                | N.C.          | 11         | 12 | N.C           |                |
|                | N.C.          | 13         | 14 | N.C.          |                |
|                | N.C.          | 15         | 16 | N.C.          |                |
|                | N.C.          | 17         | 18 | N.C.          |                |
| Power Input    | GND           | 19         | 20 | GND           | Power Input    |
|                | N.C.          | 21         | 22 | GND           | Power Input    |
|                | N.C.          | 23         | 24 | N.C.          |                |
|                | N.C.          | 25         | 26 | N.C.          |                |
|                | N.C.          | 27         | 28 | Bus_V         | Analog Input   |
|                | N.C.          | 29         | 30 | U_Imes        | Analog Input   |
|                | N.C.          | 31         | 32 | Enc_B         | Digital Input  |
|                | N.C.          | 33         | 34 | W_Imes        | Analog Input   |
| Analog Input   | Bus_Imes      | 35         | 36 | W_Vph         | Analog Input   |
| Analog Input   | V_Vph         | 37         | 38 | U_Vph         | Analog Input   |

### Connecteur CN10
| Type           | Label         | Pin number |    | Label         | Type           |
|----------------|---------------|------------|----|---------------|----------------|
|                | N.C.          | 1          | 2  | Enc_Z         | Digital Input  |
|                | N.C.          | 3          | 4  | N.C.          |                |
|                | N.C.          | 5          | 6  | N.C.          |                |
|                | N.C.          | 7          | 8  | N.C.          |                |
| Power Input    | GND           | 9          | 10 | N.C.          |                |
|                | N.C.          | 11         | 12 | N.C.          |                |
| Digital Input  | Enc_A         | 13         | 14 | N.C.          |                |
|                | N.C.          | 15         | 16 | N.C.          |                |
|                | N.C.          | 17         | 18 | N.C.          |                |
|                | N.C.          | 19         | 20 | GND           | Power Input    |
| Output         | V_PWM_H       | 21         | 22 | N.C.          |                |
| Output         | U_PWM_H       | 23         | 24 | V_Imes        | Analog Input   |
|                | N.C.          | 25         | 26 | W_PWM_L       | Output         |
|                | N.C.          | 27         | 28 | V_PWM_L       | Output         |
|                | N.C.          | 29         | 30 | U_PWM_L       | Output         |
|                | N.C.          | 31         | 32 | GND           | Power Input    |
| Output         | W_PWM_H       | 33         | 34 | N.C.          |                |
|                | N.C.          | 35         | 36 | N.C.          |                |
|                | N.C.          | 37         | 38 | N.C.          |                |

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
