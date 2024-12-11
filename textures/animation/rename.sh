#!/bin/bash

# Compteur initial
compteur=1

# Parcourir tous les fichiers .png dans le répertoire actuel
for fichier in *.png; do
    # Vérifier si le fichier existe pour éviter les erreurs si aucun .png n'est présent
    if [ -e "$fichier" ]; then
        # Définir le nouveau nom
        nouveau_nom="anim${compteur}.png"
        
        # Renommer le fichier
        mv "$fichier" "$nouveau_nom"
        
        echo "Renommé '$fichier' en '$nouveau_nom'"
        
        # Incrémenter le compteur
        compteur=$((compteur + 1))
    fi
done

echo "Renommage terminé. Total de fichiers renommés : $((compteur - 1))"

