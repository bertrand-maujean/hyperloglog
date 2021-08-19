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
 * hyperloglog.hpp
 *
 *  Created on: 4 juin 2021
 *      Author: ber
 */

#ifndef HYPERLOGLOG_H_
#define HYPERLOGLOG_H_

#include <cstdint>
#include <cstdlib>

class hyperLogLog_c {

public:
	hyperLogLog_c(int nbBits_);
	~hyperLogLog_c();

	void addElement(uint64_t);
	void addElement(char*, size_t);
	void clear();

	int64_t count();

private:
	int        nbRegisters;
	int        nbBits;

	uint64_t*  reg;
	uint64_t   rightMask;
	double     alpham2; /*constante alpha*m**2 */
};


#endif /* HYPERLOGLOG_H_ */
