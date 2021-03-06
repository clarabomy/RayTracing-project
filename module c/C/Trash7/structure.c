#define _CRT_SECURE_NO_WARNINGS
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sizeName 30


void freeAll(sParam *param) {
	//remove("data.txt");
	free(param->object);
	free(param->image.name);
	free(param->sphere);
}

int nbLine(FILE* f) {
	int c;
	int line = 0;
	while ((c=fgetc(f)) != EOF) {
		if (c == '\n') {
			++line;
		}
	}
	rewind(f);
	return line;
}

void showStruct(sParam param) {
	printf("Name: %s\n", param.image.name);
	printf("Height: %f\n", param.image.height);
	printf("Width: %f\n", param.image.width);
	printf("Background-r: %d\n", param.image.background.r);
	printf("Background-g: %d\n", param.image.background.g);
	printf("Background-b: %d\n", param.image.background.b);
	printf("Light Factor: %f\n", param.light.lightFactor);
	printf("LightPosition:\n	x: %f\n	y: %f\n	z:%f\n", param.lightSource.x, param.lightSource.y, param.lightSource.z);
	printf("ViewerPosition:\n	x: %f\n	y: %f\n	z:%f\n", param.viewerPos.x, param.viewerPos.y, param.viewerPos.z);
	printf("Nb Objects: %d\n", param.nbObjects);
	for (int i = 0; i < param.nbObjects; i++) {
		printf("Object %d:\n", i + 1);
		printf("	Formula:\n");
		for (int j = 0; j < param.object[i].formula.nbX; j++) {
			printf("		x^%d: %f\n", j + 1, param.object[i].formula.x[j]);
		}
		for (int j = 0; j < param.object[i].formula.nbY; j++) {
			printf("		y^%d: %f\n", j + 1, param.object[i].formula.y[j]);
		}
		for (int j = 0; j < param.object[i].formula.nbZ; j++) {
			printf("		z^%d: %f\n", j + 1, param.object[i].formula.z[j]);
		}		
		for (int j = 1; j <= param.object[i].nbFaces; j++) {
			printf("	Plan Equation %d:\n", j);
			printf("		a%d: %f\n", j, param.object[i].face[j - 1].planEqua.a);
			printf("		b%d: %f\n", j, param.object[i].face[j - 1].planEqua.b);
			printf("		c%d: %f\n", j, param.object[i].face[j - 1].planEqua.c);
			printf("		d%d: %f\n", j, param.object[i].face[j - 1].planEqua.d);
			printf("	Peaks(%d):\n", param.object[i].face[j - 1].nbPeaks);
			for (int k = 0; k < param.object[i].face[j - 1].nbPeaks; k++) {
				printf("		x%d: %f\n", j + 1, param.object[i].face[j - 1].peak[k].x);
				printf("		y%d: %f\n", j + 1, param.object[i].face[j - 1].peak[k].y);
				printf("		z%d: %f\n", j + 1, param.object[i].face[j - 1].peak[k].z);
			}
		}
	}
	printf("Number of spheres : %d\n", param.nbSpheres);
	for (int i = 0; i < param.nbSpheres; i++) {
		printf("	Color:\n		r : %d\n		g : %d\n		b : %d\n", param.sphere[i].color.r, param.sphere[i].color.g, param.sphere[i].color.b);
		printf("	Center:\n		x : %f\n		y : %f\n		z : %f\n", param.sphere[i].center.x, param.sphere[i].center.y, param.sphere[i].center.z);
		printf("	Radius : %f\n", param.sphere[i].radius);
	}
}

int loadFromFile(sParam *param) {
	FILE *f = fopen("data.txt", "r");
	char line[100];
	int sizeFile = nbLine(f); //on recupere le nombre de lignes du fichier
	fscanf(f, "%s", line);
	for(int i = 0; i < sizeFile; i++) {
		fscanf(f, "%s", line);
		if (!strcmp(line, "Name:")) {
			i++;
			fscanf(f, "%s", line);
			param->image.name = _strdup(line);
		}
		else if (!strcmp(line, "Height:")) {
			i++;
			fscanf(f, "%s", line);
			param->image.height = atoi(line);
		}
		else if (!strcmp(line, "Width:")) {
			i++;
			fscanf(f, "%s", line);
			param->image.width = atoi(line);
		}
		else if (!strcmp(line, "Background-color:")) {
			i++;
			for (int j = 0; j < 3; j++) {
				fscanf(f, "%s", line);
				i++;
				if (!strcmp(line, "r:")) {
					fscanf(f, "%s", line);
					i++;
					param->image.background.r = atoi(line);
				}
				else if (!strcmp(line, "g:")) {
					fscanf(f, "%s", line);
					i++;
					param->image.background.g = atoi(line);
				}
				else if (!strcmp(line, "b:")) {
					fscanf(f, "%s", line);
					i++;
					param->image.background.b = atoi(line);
				}
			}
		}
		else if (!strcmp(line, "Brightness:")) {
			i++;
			fscanf(f, "%s", line);
			param->light.lightFactor = atof(line);
		}
		else if (!strcmp(line, "LightPosition:")) {
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->lightSource.x = atof(line);
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->lightSource.y = atof(line);
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->lightSource.z = atof(line);
		}
		else if (!strcmp(line, "ViewerPosition:")) {
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->viewerPos.x = atof(line);
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->viewerPos.y = atof(line);
			i++;
			fscanf(f, "%s", line);
			i++;
			fscanf(f, "%s", line);
			param->viewerPos.z = atof(line);
		}
		else if (!strcmp(line, "Numberofobjects:")) {
			i++;
			fscanf(f, "%s", line);
			param->nbObjects = atoi(line);
			param->object = (sObject*)malloc(param->nbObjects * sizeof(sObject));
			for (int j = 0; j < param->nbObjects; j++) {
				fscanf(f, "%s", line);
				i++;
				char buffer[2];
				sprintf(buffer, "%d", j + 1);
				char searched[sizeName];
				strcpy(searched, "Object");
				strcat(searched, buffer);
				strcat(searched, ":");
				if (strcmp(line, searched)) {
					return 0;
				}
				fscanf(f, "%s", line);
				i++;
				if (strcmp(line, "Color:")) {
					return 0;
				}
				fscanf(f, "%s", line);
				i++;
				for (int k = 0; k < 3; k++) {
					if (!strcmp(line, "r:")) {
						fscanf(f, "%s", line);
						i++;
						param->object[j].color.r = atoi(line);
					}
					if (!strcmp(line, "g:")) {
						fscanf(f, "%s", line);
						i++;
						param->object[j].color.g = atoi(line);
					}
					if (!strcmp(line, "b:")) {
						fscanf(f, "%s", line);
						i++;
						param->object[j].color.b = atoi(line);
					}
					fscanf(f, "%s", line);
					i++;
					if (strcmp(line, "r:") && strcmp(line, "g:") && strcmp(line, "b:") && strcmp(line, "Formula:")) {
						return 0;
					}
				}
				fscanf(f, "%s", line);
				i++;
				for (int k = 0; k < 3; k++) {
					fscanf(f, "%s", line);
					i++;
					if (k > 0) {
						fscanf(f, "%s", line);
						i++;
					}
					int l = atoi(line);
					if (k == 0) {
						param->object[j].formula.x = (double*)malloc(l * sizeof(double));
						param->object[j].formula.nbX = l;
					}
					if (k == 1) {
						param->object[j].formula.y = (double*)malloc(l * sizeof(double));
						param->object[j].formula.nbY = l;
					}
					if (k == 2) {
						param->object[j].formula.z = (double*)malloc(l * sizeof(double));
						param->object[j].formula.nbZ = l;
					}
					int cpy = l;
					for (l; l > 0; l--) {
						fscanf(f, "%s", line);
						i++;
						char points[sizeName], nb[sizeName];
						strcpy(points, ":");
						sprintf(nb, "%d", cpy - l + 1);
						if (!strcmp(line, strcat(nb, points))) {
							fscanf(f, "%s", line);
							i++;
							if (k == 0) {
								param->object[j].formula.x[cpy - l] = atof(line);
							}
							if (k == 1) {
								param->object[j].formula.y[cpy - l] = atof(line);
							}
							if (k == 2) {
								param->object[j].formula.z[cpy - l] = atof(line);
							}
						}
					}
				}
				fscanf(f, "%s", line);
				i++;
				if (!strcmp(line, "NumberOfFaces:")) {
					fscanf(f, "%s", line);
					i++;
					param->object[j].nbFaces = atoi(line);
					param->object[j].face = (sFace*)malloc(param->object[j].nbFaces * sizeof(sFace));
					for (int l = 0; l < param->object[j].nbFaces; l++) {
						fscanf(f, "%s", line);
						i++;
						char buffer[sizeName];
						strcpy(buffer, "Face");
						char tmp[sizeName];
						sprintf(tmp, "%d", l + 1);
						strcat(buffer, tmp);
						strcat(buffer, ":");
						if (!strcmp(line, buffer)) {
							fscanf(f, "%s", line);
							i++;
							fscanf(f, "%s", line);
							i++;
							param->object[j].face[l].planEqua.a = atof(line);
							fscanf(f, "%s", line);
							i++;
							fscanf(f, "%s", line);
							i++;
							param->object[j].face[l].planEqua.b = atof(line);
							fscanf(f, "%s", line);
							i++;
							fscanf(f, "%s", line);
							i++;
							param->object[j].face[l].planEqua.c = atof(line);
							fscanf(f, "%s", line);
							i++;
							fscanf(f, "%s", line);
							i++;
							param->object[j].face[l].planEqua.d = atof(line);
						}
						fscanf(f, "%s", line);
						i++;
						if (!strcmp(line, "Numberofpeaks:")) {
							fscanf(f, "%s", line);
							i++;
							int nbPeaks = atoi(line);
							param->object[j].face[l].peak = (sPos*)malloc(nbPeaks * sizeof(sPos));
							param->object[j].face[l].nbPeaks = nbPeaks;
							for (int k = 0; k < nbPeaks; k++) {
								fscanf(f, "%s", line);
								i++;
								fscanf(f, "%s", line);
								i++;
								param->object[j].face[l].peak[k].x = atof(line);
								fscanf(f, "%s", line);
								i++;
								fscanf(f, "%s", line);
								i++;
								param->object[j].face[l].peak[k].y = atof(line);
								fscanf(f, "%s", line);
								i++;
								fscanf(f, "%s", line);
								i++;
								param->object[j].face[l].peak[k].z = atof(line);
							}
						}
					}
				}
			}
		}
		else if (!strcmp(line, "NumberOfSpheres:")) {
			i++;
			fscanf(f, "%s", line);
			param->nbSpheres = atoi(line);
			param->sphere = (sSphere*)malloc(param->nbSpheres * sizeof(sSphere));
			for (int j = 0; j < param->nbSpheres; j++) {
				i++;
				fscanf(f, "%s", line); 
				char buffer[2];
				sprintf(buffer, "%d", j + 1);
				char searched[sizeName];
				strcpy(searched, "Sphere");
				strcat(searched, buffer);
				strcat(searched, ":");
				if (strcmp(searched, line)) {
					return 0;
				}
				fscanf(f, "%s", line);
				i++;
				if (strcmp(line, "Color:")) {
					return 0;
				}
				fscanf(f, "%s", line);
				i++;
				for (int k = 0; k < 3; k++) {
					if (!strcmp(line, "r:")) {
						fscanf(f, "%s", line);
						i++;
						param->sphere[j].color.r = atoi(line);
					}
					if (!strcmp(line, "g:")) {
						fscanf(f, "%s", line);
						i++;
						param->sphere[j].color.g = atoi(line);
					}
					if (!strcmp(line, "b:")) {
						fscanf(f, "%s", line);
						i++;
						param->sphere[j].color.b = atoi(line);
					}
					fscanf(f, "%s", line);
					i++;
					if (strcmp(line, "r:") && strcmp(line, "g:") && strcmp(line, "b:") && strcmp(line, "Center:")) {
						return 0;
					}
				}
				fscanf(f, "%s", line);
				i++;
				fscanf(f, "%s", line);
				i++;
				param->sphere[j].center.x = atof(line);
				fscanf(f, "%s", line);
				i++;
				fscanf(f, "%s", line);
				i++;
				param->sphere[j].center.y= atof(line);
				fscanf(f, "%s", line);
				i++;
				fscanf(f, "%s", line);
				i++;
				param->sphere[j].center.z= atof(line);
				fscanf(f, "%s", line);
				i++;
				if (strcmp(line, "Radius:")) {
					return 0;
				}
				fscanf(f, "%s", line);
				i++;
				param->sphere[j].radius = atof(line);
			}
		}
		else { 
			return 0; 
		}
	}
	return 1;
}