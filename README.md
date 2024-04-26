# Projet IOC

## Introduction et informations

Le but de ce projet est de faire un server HTTP sur une Raspberry Pi 3, qui communique avec plusieurs ESP32 via le protocole MQTT.

## Execution

### ESP32 :
Pour lancer le code sur l'ESP32, il faut `upload` le code vers l'ESP32 depuis l'interface Arduino IDE.
Après avoir configuré le nom et le mot de passe de la connexion, ainsi que l'adresse IP du broker (Raspberry).

### Raspberry Pi :

Pour lancer le code qui lance le serveur HTTP sur la Raspberry Pi, il suffit d'exécuter la commande suivante :
```bash=
python3 matérielle/raspberry/httpinstance.py
```

#### En local :
Sur un navigateur, accédez à la page :
```
localhost:9000
```

#### En distant :
Pour récupérer l'adresse IP de la Raspberry Pi, utilisez la commande :
```
hostname -I
```
Ensuite, dans un navigateur, accédez à la page :
```
http://adresse_ip:9000
```
