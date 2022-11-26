#!/usr/bin/python3

import math
import os
import random
import re
import sys

class Solve:
    def __init__(this, n, r, c):
        this.n = n
        this.qr = r
        this.qc = c
        this.diag1_lo = max(1, 1 - c_q + r_q)
        this.diag1_hi = min(n, n - c_q + r_q)
        this.diag2_lo = max(1, c_q + r_q - n)
        this.diag2_hi = min(n, c_q + r_q - 1)
        this.horiz_lo = 1
        this.horiz_hi = n
        this.vert_lo = 1
        this.vert_hi = n

    def add_vertical_obstacle(this, obst):
        [o_r, o_c] = obst
        if o_c == this.qc:
            if o_r > this.qr and o_r <= this.vert_hi:
                this.vert_hi = o_r - 1
            elif o_r < this.qr and o_r >= this.vert_lo:
                this.vert_lo = o_r + 1
    
    def add_horizontal_obstacle(this, obst):
        [o_r, o_c] = obst
        if o_r == this.qr:
            if o_c > this.qc and o_c <= this.horiz_hi:
                this.horiz_hi = o_c - 1
            elif o_c < this.qc and o_c >= this.horiz_lo:
                this.horiz_lo = o_c + 1
    
    def add_diagonal1_obstacle(this, obst):
        [o_r, o_c] = obst
        if o_c == o_r + this.qc - this.qr:
            if o_r > this.qr and o_r <= this.diag1_hi:
                this.diag1_hi = o_r - 1
            elif o_r < this.qr and o_r >= this.diag1_lo:
                this.diag1_lo = o_r + 1

    def add_diagonal2_obstacle(this, obst):
        [o_r, o_c] = obst
        if o_c == -o_r + this.qc + this.qr:
            if o_r > this.qr and o_r <= this.diag2_hi:
                this.diag2_hi = o_r - 1
            elif o_r < this.qr and o_r >= this.diag2_lo:
                this.diag2_lo = o_r + 1

    def add_obstacle(this, obst):
        this.add_vertical_obstacle(obst)
        this.add_horizontal_obstacle(obst)
        this.add_diagonal1_obstacle(obst)
        this.add_diagonal2_obstacle(obst)

    def count_fields(this):
        return sum([this.diag1_hi - this.diag1_lo, this.diag2_hi - this.diag2_lo, this.horiz_hi - this.horiz_lo, this.vert_hi - this.vert_lo])
        

def queensAttack(n, k, r_q, c_q, obstacles):
    solver = Solve(n, r_q, c_q)
    
    for obst in obstacles:
        solver.add_obstacle(obst)

    return solver.count_fields()

if __name__ == '__main__':
    nk = input().split()
    n = int(nk[0])
    k = int(nk[1])
    r_qC_q = input().split()
    r_q = int(r_qC_q[0])
    c_q = int(r_qC_q[1])
    obstacles = []

    for _ in range(k):
        obstacles.append(list(map(int, input().split())))

    result = queensAttack(n, k, r_q, c_q, obstacles)
    print(result)
