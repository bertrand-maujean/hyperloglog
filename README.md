# Tiny HyperLogLog lib for C++


## Building / compatibility
Work on Linux Debian / GCC
A small incursion in assembly will prevent porting on other arch than x86_64

## Usage
See example in test-hll.cpp and hyperloglog.cpp, the code is very short.
Argument 'nbBits' to class'constructor must be within range (see source). Erroneous values are not correctly handled (assert)

## Test sample
Launch test-hll and see test-result.txt

## References
- [Wiki](https://en.wikipedia.org/wiki/HyperLogLog)
- [HyperLogLog: the analysis of a near-optimal cardinality estimation algorithm](http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf)

## Licence
This work is released under GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007 by Bertrand Maujean
See : http://www.gnu.org/licenses/agpl.html and file LICENSE.txt in distribution folder.
