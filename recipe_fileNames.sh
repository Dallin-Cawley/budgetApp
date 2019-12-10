#!/bin/sh

for dir in Recipes/*
do
	for dir2 in "$dir"/*
	do
		for filePath in "$dir2"
		do
		      echo $filePath >> "recipe_filePath.txt"
		done
	done
done
