% name rule:
% matrix prefix:
% D means 'diag', S means 'skew', d means 'delta'
%
% variable name:
% x0 := p0_x
% z10 := p0_z - p1_z


%% LaserOdometry derivation
syms x0 y0 z0 real
syms x10 y10 z10 real
syms x12 y12 z12 real
syms x13 y13 z13 real

Dd13 = diag([x13 y13 z13]);
Sd12 = [0 -z12 y12; z12 0 -x12; -y12 x12 0];
S0 = [0 -z0 y0; z0 0 -x0; -y0 x0 0];
d10 = [x10 y10 z10]';

disp('LaserOdometry')
% use 2 points to represent a line
disp('point-line')
J = Sd12 * [-S0 eye(3)]
r = Sd12 * d10
% use 3 points to represent a plane
disp('point-plane')
J = Dd13 * J
r = Dd13 * r

%% LaserMapping derivation
syms x1 y1 z1
syms vx vy vz
Sv = [0 -vz vy; vz 0 -vx; -vy vx 0];
Dv = diag([vx vy vz]);

disp('LaserMapping')
% use a point and a unit direction vector to represent a line
disp('point-line')
J = Sv * [-S0 eye(3)]
r = Sv * d10
% use a point and a unit normal vector to represent a plane
disp('point-plane')
J = Dv * [-S0 eye(3)]
r = Dv * d10
