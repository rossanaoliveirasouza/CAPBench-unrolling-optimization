#
# Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#

# Builds all kernels.
all: fast fn gf is km lu tsp

# Builds FAST kernel.
fast:
	cd FAST && $(MAKE) all

# Builds FN kernel.
fn:
	cd FN && $(MAKE) all

# Builds GF kernel.
gf:
	cd GF && $(MAKE) all

# Builds IS kernel.
is:
	cd IS && $(MAKE) all

# Builds KM kernel.
km:
	cd KM && $(MAKE) all

# Builds LU kernel.
lu:
	cd LU && $(MAKE) all

# Cleans compilation files.
clean:
	cd FAST && $(MAKE) clean
	cd FN && $(MAKE) clean
	cd GF && $(MAKE) clean
	cd IS && $(MAKE) clean
	cd KM && $(MAKE) clean
	cd LU && $(MAKE) clean
