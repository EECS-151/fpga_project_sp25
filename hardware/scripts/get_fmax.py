#!/usr/bin/env python3

import os
import argparse

def get_fmax(f):
  for line in f:
    if line.startswith('| Design Timing Summary'):
      next(f)
      line = next(f).strip()
      while not(line.startswith('WNS')):
        line = next(f).strip()
      next(f)
      line = next(f)
      x = line.split()
      wns = float(x[0])
      if wns < 0:
        print(f"ERROR: Negative slack. Timing violated. WNS(ns) = {wns}")

    if line.startswith('| Clock Summary'):
      next(f)
      line = next(f).strip()
      while not(line.startswith('cpu_clk_int')):
        line = next(f).strip()
      x = line.split()
      return float(x[-1])

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('rpt', action='store', help='timing summary report')

  args = parser.parse_args()
  if os.path.isfile(args.rpt):
    f = open(args.rpt, 'r')
  else:
    print(args.rpt + ' not found')
    exit()

  print('Fmax: ' + str(get_fmax(f)))
