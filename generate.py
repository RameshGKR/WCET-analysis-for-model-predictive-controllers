from shutil import copytree
import numpy as np
import casadi as cs
from impact import MPC, MultipleShooting
import matplotlib.pyplot as plt

# Constants
Tf = 2
Nhor = 50
Nsim = 200
x_initial = [0.5, 0, 0, 0]
x_desired = [0, 0, 0, 0]
dt = Tf/Nhor

# MPC and model with parameters
mpc = MPC(T=Tf)
model = mpc.add_model('model_definition', 'model_definition.yaml')
x_current = mpc.parameter('x_current', model.nx)
x_final = mpc.parameter('x_final', model.nx)

# Objective
mpc.add_objective(mpc.integral(model.F**2 + 100*model.pos**2))

# Boundary constraints
mpc.subject_to(mpc.at_t0(model.x) == x_current)
mpc.subject_to(mpc.at_tf(model.x) == x_final)

# Path constraints
mpc.subject_to(-2 <= (model.F <= 2 ))
mpc.subject_to(-2 <= (model.pos <= 2), include_first=False)

# Set parameter values
mpc.set_value(x_current, x_initial)
mpc.set_value(x_final, x_desired)

# Select the method
mpc.method(MultipleShooting(N=Nhor,M=1,intg='rk'))

# Select sqpmethod + qrqp as the solver
mpc.solver("sqpmethod", {
    "qpsol": "qrqp",
    "print_header": False,
    "print_iteration": False,
    "print_time": False,
    "print_status": False,
    "qpsol_options": {
        "print_header": False,
        "print_iter": False,
        "print_info": False,
    }
})

# Generate code for MPC controller
mpc.export(
    name="mpc", 
    use_codegen=True
)

# Copy folder to src folder
copytree("mpc_build_dir", "src/mpc_build_dir", dirs_exist_ok=True)

# Extract system model
system_model = mpc._method.discrete_system(mpc)

# Simulate
x_log = np.ndarray((Nsim, model.nx))
u_log = np.ndarray((Nsim, model.nu))

x_meas = x_initial
for i in range(Nsim):
    print(f"Timestep {i+1}/{Nsim}")

    ## Find optimal control input
    mpc.set_value(x_current, x_meas)
    sol = mpc.solve()
    u_opt = sol.sample(model.F, grid='control')[1][0]

    ## Log
    x_log[i] = np.squeeze(x_meas)
    u_log[i] = u_opt

    ## Update system state with optimal control input
    x_meas = system_model(x0=x_meas, u=u_opt, T=dt)['xf']

    ## Add measurement noise
    meas_noise = 5e-4*(cs.DM.rand(x_meas.shape)-cs.vertcat(1,1,1,1)) # 4x1 vector with values in [-1e-3, 1e-3]
    x_meas += meas_noise

    ## Add disturbance at halftime
    if i == 50:
        disturbance = cs.vertcat(0,0,-1e-1,0)
        x_meas = x_meas + disturbance

# Save simulation results to header file
with open("src/input.h", 'w') as h_file:
    h_file.write(f"const static int INPUT_ROWS = {len(x_log)};\n")
    h_file.write(f"const static int INPUT_COLS = {len(x_log[0])};\n")
    h_file.write(f"const static double INPUT[INPUT_ROWS][INPUT_COLS] =" + "{")
    h_file.write(",".join(["{" + ','.join(str(row)) + "}" for row in x_log]))
    h_file.write("};")

# Plot simulation results
if input("Show simulation results (y/n)? ") != "y":
    quit()

t_log = np.linspace(0, Nsim*dt, Nsim)

## Plot position
fig, ax1 = plt.subplots()
ax1.plot(t_log, x_log[:, 0], 'r-')
ax1.set_xlabel('Time [s]')
ax1.set_ylabel('Cart position [m]', color='r')
ax1.tick_params('y', colors='r')
ax1.axhline(x_desired[0], color='r', linestyle=':')

## Plot pendulum angle
ax2 = ax1.twinx()
ax2.plot(t_log, x_log[:, 1], 'b-')
ax2.set_ylabel('Pendulum angle [rad]', color='b')
ax2.tick_params('y', colors='b')
ax2.axhline(x_desired[1], color='b', linestyle=':')

fig.tight_layout()
plt.show()
