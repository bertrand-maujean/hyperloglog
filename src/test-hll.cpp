/*
    hyperloglog tiny library for C++
    Copyright (C) 2021 Bertrand Maujean

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


/*
 * test-hll.cpp
 *
 *  Created on: 5 juin 2021
 *      Author: ber
 */

#include <cstdlib>
#include <cstdint>
#include <stdio.h> /* printf */
#include <cassert>
#include <ctime>


#include "hyperloglog.h"


void test(size_t nelems, int nbBits) {
	uint64_t* list=(uint64_t*)malloc(nelems * sizeof(uint64_t));
	assert(list);

	hyperLogLog_c* hll = new hyperLogLog_c(nbBits);

	/* initialise des valeurs aléatoires en nombre connu
	for (int n=0; n<nelems; n++) {
		list[n] = (uint64_t)random() + (((uint64_t)random())<<32);
	}

	/* Insert toutes ces valeurs

	for (int n=0; n<nelems; n++) {
		hll->addElement(list[n]);
	}*/

	for (int n=0; n<nelems; n++) {
		uint64_t v = (uint64_t)random() + (((uint64_t)random())<<32);
		hll->addElement(v);
	}



	/* Affiche le résultat du décompte */
	int64_t c=hll->count();
	double r =c;
	r = 100.0 * r/nelems;
	printf("nbBits=%2d\tcompté=%10d  réel=%10d    compté/réel=%03.2f%%\n", nbBits, c, nelems, r);
	delete hll;
	free(list);

}


int main(int argc, char* argv[], char** env) {
	srandom((unsigned int)time(NULL));
	for (int nbBits=4; nbBits<13; nbBits++) {
		for (long int nbE=10; nbE < 10000000000L; nbE=nbE*10) {
			test(nbE,  nbBits);
		}
		puts("");
	}
	return 0;
}

