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

# ------------------------------------------------------------------------------
# Actual system in Open Loop
# ------------------------------------------------------------------------------

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

# ------------------------------------------------------------------------------
# Estimation with LQR
# ------------------------------------------------------------------------------
# Initial Parameters
R = 1;
Q = [25 0 0; 0 10 0; 0 0 20];
error = 0.75;
# First estimation
Klqr = lqr(A,B,Q,R);

printf("LQR Iteration:\n");
Klqr

# New System State Matrix
Ad_lqr = [A-B*Klqr];
Bd_lqr = [B];
Cd_lqr = [C];
Dd_lqr = [D];

# Create system in Closed Loop
sys_cl = ss(Ad_lqr,Bd_lqr,Cd_lqr,Dd_lqr,'statename',states,'inputname',inputs,'outputname',outputs);


# ------------------------------------------------------------------------------
# Simulation - Perturbation response
# ------------------------------------------------------------------------------
# Creating a dummy stimulus
t = 0:0.01:1;
for i = 1:size(t)(2)
    if (i < 5 || i > 20)        # 15 steps -> 150ms
        uc(i) = 0;
    else
        uc(i) = 8;   # 8V
    endif
endfor

# Simulate both systems
[ycl,t0,xcl]=lsim(sys_cl,uc,t);

# Get the control action (Xk)
Xk_cl = Klqr*xcl'; #'

# Equivalency between voltage and torque
# 8.00V <-> 2.3734 kg.cm (This will be the maximum torque accepted in the system)
uc = uc(:)*(2.3734/8);            # Input
Xk_cl = Xk_cl(:)*(2.3734/8);    # Control action - LQR

# Plot Closed Loop - LQR
figure("name", "Closed Loop with LQR - 150ms perturbation");
#ycl = ycl*(1/max(ycl));
#uc = uc*(1/max(uc));
#plot(t, ycl, 'color', 'red');
#hold on;
#plot(t, uc, 'color', 'green');
[AX,H1,H2] = plotyy(t,Xk_cl,t,ycl);
set(get(AX(1),'Ylabel'),'String','Input Torque [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
hold on;
plot(t, uc, 'color', 'green');
title('Response with LQR Control - 150ms perturbation');
legend('Control Action', 'Perturbation 2.37 kg-cm', 'Output');



