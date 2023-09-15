

import pylab as plt
import numpy as np

from impact import Impact

impact = Impact("mpc",src_dir="..")

# Example: how to set a parameter
val_x_final = [0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000]
impact.set("p", "x_final", impact.EVERYWHERE, impact.FULL, val_x_final)
        
print("Solve a single OCP (default parameters)")
impact.solve()

# Get model_definition.pos solution trajectory
print(impact.get("x_opt", "model_definition.pos", impact.EVERYWHERE, impact.FULL))

# Get solution trajectory
x_opt = impact.get("x_opt", impact.ALL, impact.EVERYWHERE, impact.FULL)

# Plotting


_, ax = plt.subplots(2,1,sharex=True)
ax[0].plot(x_opt.T)
ax[0].set_title('Single OCP')
ax[0].set_xlabel('Sample')

print("Running MPC simulation loop")

history = []
for i in range(100):
  impact.solve()

  # Optimal input at k=0
  u = impact.get("u_opt", impact.ALL, 0, impact.FULL)

  # Simulate 1 step forward in time
  # (TODO: use simulation model other than MPC model)
  x_sim = impact.get("x_opt", impact.ALL, 1, impact.FULL)

  # Update current state
  impact.set("x_current", impact.ALL, 0, impact.FULL, x_sim)
  history.append(x_sim)

# More plotting
ax[1].plot(np.hstack(history).T)
ax[1].set_title('Simulated MPC')
ax[1].set_xlabel('Sample')
plt.show()



      