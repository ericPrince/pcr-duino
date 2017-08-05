# Home-made Arduino PCR Machine

PCR is a method for DNA replication. The DNA is put in with a polymerase and heated and cooled to various temperatures, allowing the polymerase to go to work. For an explanation of PCR, see the Wikipedia article.

## The Hardware

This setup uses a 120 W incandescent light bulb as the heating element and a 12 V fan (from an old computer) as the cooling element. They are controlled by an Arduino with relays (using an Arduino relay shield makes the wiring really easy, but isn't required | TODO: add schematic). The housing for the PCR machine is PVC tube with holes cut out to put the samples in. The light bulb goes in the middle of the housing. The temperature sensor is put through one of the cut-outs as if it is a sample. This setup used small temperature sensor ICs rather than thermistors.

## The Code

TODO