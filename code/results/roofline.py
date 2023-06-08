import matplotlib.pyplot as plt
import numpy as np

def f(x):
    if x * 76.8 <= 537.6:
        return x * 76.8
    else:
        return 537.6
    
fig, ax = plt.subplots()
    
x = np.linspace(0, 100, 10000)
plt.ylim(1, 1000)

f2 = np.vectorize(f)
y = f2(x)

plt.loglog(x, y, label="SH Ridge Point", color="blue")
plt.loglog(x, y, label="Intel CPU", color="orange")

plt.title("Roofline Analysis")
plt.xlabel("Operational Intensity (Flops/byte)")
plt.ylabel("Performance (Gflops/s)")
plt.legend(loc="upper left")
ax.axvline(537.6/76.8, linestyle='--', color="orange") 
ax.axvline(0.03, linestyle='--', color="blue") 

plt.show()
plt.savefig('roofline.png')
plt.close()