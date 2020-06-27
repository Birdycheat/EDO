#pragma once

void euler_explicite(fonction *, const eq_diff);

void euler_implicite(fonction *, const eq_diff);

void crank_nicolson(fonction *, const eq_diff);

void RK4(fonction *, const eq_diff);