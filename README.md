# SAE-R101-Candy-Crush
Un jeu Candy Crush like réalisé en C++ entièrement jouable dans le terminal de commandes

### Comment utiliser git ? tuto par Alex :)
- Générer la clé ssh (se placer au préalable dans ~) : https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
- Faire un cat de la clé (PUBLIQUE !!) et la copier coller dans 'Key' quand vous créez un token
- Créer un dossier où vous voulez mettre le code source
- faire le 'git clone [url] .'
- et pour finir les commandes de base (status, add, commit, etc)

### Idée de structure du menu de l'écran titre ?
```
.
├── 1 - Jouer
├── 2 - Table des High Scores
│   ├── 1 - Sauvegarder la table
│   ├── 2 - Charger une table
│   └── 3 - Retour
├── 3 - Options
│   ├── 1 - Langue
│   │   ├── 1 - Francais
│   │   └── 2 - Anglais
│   ├── 2 - Mode de déplacement
│   │   ├── 1 - Case par case (séquence de touches)
│   │   ├── 2 - Instantané (coordonnées)
│   │   └── 3 - Retour
│   └── 4 - Retour
├── A propos
│   └── 1 - Retour
└── Quitter
```
