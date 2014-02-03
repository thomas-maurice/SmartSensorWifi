# Projet 42 : Smart Sensor Wifi
*Binôme Thomas Maurice - Benoit Maliar, IMA4SC*

## Énoncé initial du projet
L'objectif du projet consiste en la conception et la réalisation de
capteurs autonomes communiquant en WiFi afin de pouvoir remonter
régulièrement des informations sur l'état des salles de cours.
Les capteurs seront par exemple des détecteurs de lumières,
de pression, de qualité de l'air, ...

La communication sera obligatoirement réalisée en WiFi sur le réseau
de l'université en respectant les contraintes de sécurité (WPA2, ...).

Deux options sont possibles :

 * Refaire complètement une carte avec un microcontroleur et une puce wifi
 (comme par exemple les [spark](https://www.spark.io/))
 * Réaliser un shield pour raspberry pi contenant les différents capteurs. 

## Analyse rapide du sujet
On a ici affaire à un réseau de capteurs reliés à une base de donnée centrale
qui est chargée d'interroger régulièrement les différents capteurs de manière
à pouvoir présenter à un utilisateur un état des différentes pièces dans
lesquelles on aura disposé les capteurs. Cela peut notemment impliquer :

 * Un accès à ces données via une interface web
 * Un accès à ces données via une application mobile
 * Un accès à ces données via un programme desktop
 
On identifie donc deux parties au projet :

 * La partie capteur
 * La partie serveur

Et on déduis donc l'architecture de la Figure 1.

![Diagramme fonctionnel](DiagrammeFonctionnel.jpg)

## Cahier des charges
### Spécifications des capteurs
Les caractéristiques souhaitées pour les capteurs sont :

 * Être capable de mesurer l'environnement dans lequel évolue le capteur
   (Pression, température, lumière, présence, ouverture de porte...)
 * Contacter le seuveur via le WiFi pour actualiser la base.
 * Éventuellement, être reconfigurable à distance.
 * Éventuellement être capable de gérer sa consomation d'énergie.
 * Agir en temps que datalogger si le réseau n'est pas accessible.

### Spécifications du serveur
Les caractéristiques souhaitées pour le serveur sont :

 * Être capable de contacter ou d'être contacté par les capteurs via le réseau.
 * Respecter les contraintes de sécurité (WPA2)
 * Être capable d'authentifier les clients
 * Stocker les données reçues dans une base de données et éventuellement
   faire des calculs et des statistiques sur ces données.
 * Présenter sous format compréhensibles les données au client (web ou appli)
 * Vérifier l'état des capteurs et notifier un responsable en cas d'anomalie
   (déconnexion du réseau, valeur anormale d'un capteur...)

## Propositions de solutions technologiques
### Les capteurs
Nous proposons de réaliser une carte basée sur un ATmega328 dans lequel
on pourra flasher du code Arduino. Pour gérer le WiFi, nous proposons
une solution utilisant le board CC3000 d'Adafruit 
[lien ici](http://www.adafruit.com/products/1469).
L'avantage de cette solution est que la carte est optimisée pour les
breadboards et peut du coup facilement être clipsée sur la carte.
Elle possède également l'avantage d'être fournie avec la bibliothèque
Arduino qui va bien (et qui est bien open source) de manière à
pouvoir être pilotée depuis un Arduino ou dans notre cas un AVR tout
simple. Enfin, le dernier avantage est qu'Adafruit travaille en mode
*Open Hardware* ce qui signifie que les plans de la carte sont
disponibles en ligne, ce qui nous permettrait d'intégrer la carte WiFi au
sein de notre projet facilement dans un second temps.

Dans un premier temps, on se concentrera sur la mise en place
d'un prototype fonctionnel a base d'un simple capteur de température. On
étendra ensuite les capacités de la chose à des capteurs peut être
plus complexes style I2C ou SPI.

### Le serveur
On propose une solution à base d'une machine sous Linux (Raspberry Pi
pour une version plus compacte
ou un vrai serveur pour une version destinée à administrer des
réseaux de capteurs de taille plus importante.

Le SGBD utilisé serait **MySQL** ou **SQLite**.

La partie web du serveur destinée à présenter à l'utilisateur une vue
des données serait développée en PHP/HTML5/CSS3.
La partie serveur qui recevra les flots de communication des capteurs
serait programmée en Python. Cette partie servira
à recueillir les données des capteurs et à les formater pour les insérer
dans la base. Éventuellement des opérations
pourront être effectuées sur ces données, exemple transformer un entier
8 bits en une température entre 20° et 30°.
