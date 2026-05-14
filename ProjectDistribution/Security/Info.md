# PIR_MadMax

PIR (Projet Initiation à la Recherche) 4AE-SE INSA Toulouse

Projet MadMax

# Bluetooth jamming: 
- Bluetooth utilise les frequences de 2.4GHz à 2.483GHz.
- Flipper zero a comme moyen de jammer une frequence donné, si on sait sur quelle bande le µC envoie, on peut facilement le manipuler/arrêter.
| Categorie | URL |
| ----------|--------|
| Sub-GHz jamming | https://github.com/SHUR1K-N/Flipper-Zero-Sub-GHz-Jamming-Files |
| GHz-jamming | https://github.com/huuck/FlipperZeroNRFJammer?tab=readme-ov-file |

**Jamming fonctionne**, avec le FlipperZero. On a utilisé un nrf24 jammer. 

Pour manipuler:

- Va sur bluetooth (GPIO bridge 5V!) et lance nrf24_jammer_OF, puis joue sur les differents tailles de bandes!


### **Liens utiles**

**Flipper Zero Bluetooth Jammer** : https://www.youtube.com/watch?v=mSC-Wmy9f_E&t=6s

Un article interessant qui s'agit des differents types d'attaque à **Bluetooth**: 

- https://www.sciencedirect.com/science/article/pii/S2772918424000079
- https://www.pentestpartners.com/security-blog/start-hacking-bluetooth-low-energy-today-part-1/
- https://www.forbes.com/sites/alexvakulov/2025/02/20/11-types-of-bluetooth-attacks-and-how-to-protect-your-devices/ 
- https://hackers-arise.com/bluetooth-hacking-part-1-getting-started-with-bluetooth/
- https://apps.apple.com/us/app/bluetooth-serial-connect/id6449396821

### Avec le module Bluetooth

Lien: https://www.scribd.com/document/681803015/Bluetooth-TRx-Module-New

Image: 


# Comment choisir le bon repo dans ArduinoIDE: 

File->Preferneces->"Change path"

## Comment se connecter au module Bluetooth dans environnement Linux:

**Adresse MAC** Module Bluetooth HC-05: 98:D3:51:FF:08:5E

# **Première fois:**

**Handshake:**

```
sudo bluetoothctl
-> power on
-> agent on
-> scan on
-> pair 98:D3:51:FF:08:5E
-> Ctrl + D
```

**Se connecter au module:**

```
sudo rfcomm connect 0 98:D3:51:FF:08:5E 1

sudo stty -F /dev/rfcomm0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts 

sudo su -c "echo 'message' > /dev/rfcomm0"

sudo rfcomm release 0
```

# Après être connecté une fois:

```
sudo rfcomm release 0

sudo rfcomm connect 0 98:D3:51:FF:08:5E 1

sudo stty -F /dev/rfcomm0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts 
```

**Ecrire un message:** 
```
sudo su -c "echo 'message' > /dev/rfcomm0"
```
**Ecrire via screen:**
```
sudo screen /dev/rfcomm0
```
Pour quitter le screen:
```
 CTRL + A + :quit
```

