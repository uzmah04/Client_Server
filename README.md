# Client_Server
## Client envoie des requêtes au serveur 


> Les étapes à suivre:

- Copier et cloner le référentiel git et allez dans le dossier Client_Server
  - `git clone https://github.com/uzmah04/Client_Server.git`
  - `cd Client_Server`
  
- Ouvrez un terminal et exécutez le code suivant
  - `./Server.c`

- Ouvrez un deuxième terminal et exécutez le code suivant
  - `./Client.c`

- À ce moment, le client peut envoyer la demande souhaitée au serveur en choisissant l'un des numéros.

- Si jamais le programme est en attente, vous pouvez appuyer sur `ctrl c` pour quitter.

- Pour la requête no.1 le client vas recevoir un message de quel document il veut et et à ce moment le client peut demander le document disponible sur le projet git. Et si jamais le client demande un autre document(.txt) qui n'est pas disponible, alors il va recevoir un document vide.

- Pour la requête no.3 le client peut supprimer le document qu'il souhaite.

- Et pour la dernière requête, le programme s'arrêtera.

- Si jamais le client fait une requête qui n'existe pas, le serveur répondra avec un message d'erreur (`error`) et le programme continuera.


## dev branch

- La branche dev se compose de 3 types de code respectivement:

  1. Cli_1.c et Serv_1.c
  ```
  Copiez et collez les codes suivants et exécutez-les comme indiqué en haut.
  Celui-ci est un programme simple juste pour envoyer au client un message «Hello World».
  Et le programme s'arrête tout de suite.
  
  ```
  2. Cli.c et Serv.C
  ```
  Ce programme envoie également le message «Hello World», mais il envoie et affiche aussi le nombre d'octets du message.
  Et le programme s'arrête tout de suite.
  
  ```
  
  3. Client.c et Server.c
  ```
  Dans ce programme nous avons utilisé un `switch case` pour montrer que quand le programme est exécutée le client reçoit les 3 types de requêtes et il doit en choisir un .
  C'est une façon plus simple et brève de communiquer avec le client et de comprendre.
  
  (Notez que ce code montre juste la utilisation d'un switch case et ce n'est pas le programme finale.)
  
  ```
  
  
