% PIR Charrette
% Modélisation du système dynamique en fonctions de transfert

clear all;
close all;
clc;

p = 23 ; % nombre de paires de pôles du moteur PMSM

% U = w_elec * psi_m
% w_elec = p * w_meca
% w_meca = v / rayon

U_alim = 48 ; % alimentation
R_roue = 0.33 ; % rayon de la roue
v_max = 13.9 ; % vitesse en m/s

w_meca = v_max / R_roue ; % vitesse mécanique
w_elec = p * w_meca ; % vitesse électrique
psi_m = U_alim / w_elec ; % flux rotorique couplé au stator

K_psi = 3/2 * p * psi_m ; % (N.m/A) Gain du moteur

M_tot = 50 ; % kg

J_tot = M_tot * R_roue^2 ;

f = 5 ; % N/(m.s) coefficient visqueux de friction

%%

A = [0, 1 ; 0, -f/J_tot] ;
B = [0; K_psi/J_tot] ;
C = [1, 0] ;
D = 0 ;

%%
sys = ss(A, B, C, D) ;

sim("sys_dynamique.slx") ;
figure(1);
plot(ans.simu.Time, ans.simu.Data, 'red');
title('Response of the Dynamic System');
xlabel('Time (s)');
ylabel('Output');
grid on;
hold on;
t = 0:0.1:10 ;

step(sys, t)
legend('Simulink', 'Matlab');

%%
K = place(sys)

%%
cl_sys = ss(A-B*K, -B*inv(C*inv(A-B*K)*B), C, D)