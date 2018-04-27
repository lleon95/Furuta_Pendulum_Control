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

# Create system in Open Loop
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

# New System State Matrix
Ad = [A-B*K];
Bd = [B];
Cd = [C];
Dd = [D];

# Create system in Closed Loop
sys_cl = ss(Ad,Bd,Cd,Dd,'statename',states,'inputname',inputs,'outputname',outputs);

# Creating a dummy stimulus
t = 0:0.01:5;
for i = 1:size(t)(2)
    if (i < 5 || i > 20)
        u(i) = 0;
    else
        u(i) = 100;
    endif
endfor

# Simulate both systems
[ycl,t,x]=lsim(sys_cl,u,t);
[yss,t,x]=lsim(sys_ss,u,t);

# Normalise
yss = yss*(1/max(yss));

# Plot Closed Loop
figure(1);
[AX,H1,H2] = plotyy(t,u,t,ycl);
set(get(AX(1),'Ylabel'),'String','Stimulus')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle')
title('Step Response with LQR Control');

# Plot Open Loop
figure(2);
[AX,H1,H2] = plotyy(t,u,t,yss);
set(get(AX(1),'Ylabel'),'String','Stimulus')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle')
title('Step Response in Open Loop');





