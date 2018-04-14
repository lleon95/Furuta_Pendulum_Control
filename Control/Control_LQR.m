# --------------------------------------------------
# Instituto Tecnológico de Costa Rica
# Escuela de Ing. Electrónica
# Control Automático
# Estudiantes:
#   Luis Leon
#   Esteban Hidalgo
#   Diego Aguilar
# Semestre I - 2018
# --------------------------------------------------

# Load control package
pkg load control

# System Description in a Controlable form
A = [0 1 0; 0 0 1; 377 81.44 -4.468];
B = [0; 10.41; 0];
C = [1 0 0];
D = 0;
states = {'theta' 'omega' 'alpha'};
inputs = {'u'};
outputs = {'tetha'};
sys_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);

# Initial Parameters
R = 1;
Q = [1 0 0; 0 1 0; 0 0 1];
error = 0.75;
qError = 1/(error*error);
Q = qError*Q;
# First estimation
K = lqr(A,B,Q,R);

printf("First Iteration:\n");
K

# New System
Ad = [A-B*K];
Bd = [B];
Cd = [C];
Dd = [D];

sys_cl = ss(Ad,Bd,Cd,Dd,'statename',states,'inputname',inputs,'outputname',outputs);

# Plotting
t = 0:0.01:5;
for i = 1:size(t)(2)
    if (i < 5 || i > 20)
        u(i) = 0;
    else
        u(i) = 100;
    endif
endfor

[ycl,t,x]=lsim(sys_cl,u,t);
[yss,t,x]=lsim(sys_ss,u,t);
yss = yss*(1/max(yss));
[AX,H1,H2] = plotyy(t,u,t,ycl);
set(get(AX(1),'Ylabel'),'String','Pendulum Angle - Open')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle - Close')
title('Step Response with LQR Control')






