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
Q = [700 0 0; 0 200 0; 0 0 400];
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
# Estimation with State Feedback
# ------------------------------------------------------------------------------
printf("STATE FEEDBACK Iteration:\n");
Kb = [-39.2 1.2 0.634]

# New System State Matrix
Ad_fb = [A-B*Kb];
Bd_fb = [B];
Cd_fb = [C];
Dd_fb = [D];

# Create system in Closed Loop
sys_fb = ss(Ad_fb,Bd_fb,Cd_fb,Dd_fb,'statename',states,'inputname',inputs,'outputname',outputs);
# ------------------------------------------------------------------------------
# Simulation - Perturbation response
# ------------------------------------------------------------------------------
# Creating a dummy stimulus
t = 0:0.01:5;
for i = 1:size(t)(2)
    if (i < 5 || i > 20)        # 15 steps -> 150ms
        u(i) = 0;
    else
        u(i) = 8;   # 8V
    endif
endfor

# Simulate both systems
[ycl,t,xcl]=lsim(sys_cl,u,t);
[yss,t,xss]=lsim(sys_ss,u,t);
[yfb,t,xfb]=lsim(sys_fb,u,t);

# Get the control action (Xk)
Xk_cl = Klqr*xcl'; #'
Xk_fb = Klqr*xfb'; #'

# Equivalency between voltage and torque
# 8.00V <-> 2.3734 kg.cm (This will be the maximum torque accepted in the system)
u = u(:)*(2.3734/8);            # Input
Xk_cl = Xk_cl(:)*(2.3734/8);    # Control action - LQR
Xk_fb = Xk_fb(:)*(2.3734/8);    # Control action - SF

# Plot Closed Loop - LQR
figure("name", "Closed Loop with LQR - 150ms perturbation");
[AX,H1,H2] = plotyy(t,Xk_cl,t,ycl);
set(get(AX(1),'Ylabel'),'String','Input Torque [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
hold on;
plot(t, u, 'color', 'green');
title('Step Response with LQR Control - 150ms perturbation');
legend('Control Action', 'Perturbation', 'Output');

# Plot Closed Loop - State Feedback
figure("name", "Closed Loop with State Feedback - 150ms perturbation");
[AX,H1,H2] = plotyy(t,Xk_fb,t,yfb);
set(get(AX(1),'Ylabel'),'String','Input Torque [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
hold on;
plot(t, u, 'color', 'green');
title('Step Response with State Feedback - 150ms perturbation');
legend('Control Action', 'Perturbation', 'Output');

# Plot Open Loop
figure("name", "Open Loop - 150ms perturbation");
[AX,H1,H2] = plotyy(t,u,t,yss);
set(get(AX(1),'Ylabel'),'String','Perturbation [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
title('Step Response in Open Loop - 150ms perturbation');

# ------------------------------------------------------------------------------
# Simulation - Impulse Response
# ------------------------------------------------------------------------------
# Creating a dummy stimulus
ti = 0:0.01:1;
for i = 1:size(t)(2)
    if (i < 5)        # 15 steps -> 150ms
        ui(i) = 0;
    else
        ui(i) = 8;   # 8V
    endif
endfor

# Simulate both systems
[ycl,t,xcl]=lsim(sys_cl,ui,ti);
[yfb,t,xfb]=lsim(sys_fb,ui,ti);

# Get the control action (Xk)
Xk_cl = Klqr*xcl'; #'
Xk_fb = Klqr*xfb'; #'

# Equivalency between voltage and torque
# 8.00V <-> 2.3734 kg.cm (This will be the maximum torque accepted in the system)
ui = ui(:)*(2.3734/8);            # Input
Xk_cl = Xk_cl(:)*(2.3734/8);    # Control action

# Plot Closed Loop - LQR
figure("name", "Closed Loop with LQR - Impulse Response");
[AX,H1,H2] = plotyy(t,Xk_cl,ti,ycl);
set(get(AX(1),'Ylabel'),'String','Input Torque [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
hold on;
plot(t, ui, 'color', 'green');
title('Step Response with LQR Control - Impulse Response');
legend('Control Action', 'Perturbation', 'Output');

# Plot Closed Loop - State Feedback
figure("name", "Closed Loop with State Feedback - Impulse Response");
[AX,H1,H2] = plotyy(t,Xk_fb,ti,yfb);
set(get(AX(1),'Ylabel'),'String','Input Torque [kg.cm]')
set(get(AX(2),'Ylabel'),'String','Pendulum Angle [rad]')
hold on;
plot(t, ui, 'color', 'green');
title('Step Response with State Feedback Control - Impulse Response');
legend('Control Action', 'Perturbation', 'Output');



