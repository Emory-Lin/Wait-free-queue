import matplotlib.pyplot as plt


plt.figure(figsize=(20, 10), dpi=100)
round = ['100000', '200000', '300000', '400000', '500000', '600000', '700000','800000','900000','1000000']
wait_free_4 = [0.00948703, 0.0144622, 0.0191364, 0.0286822, 0.0355934, 0.0419054, 0.057305, 0.0659972, 0.0775802, 0.105996]
stack_4 = [0.0151394, 0.0270609, 0.0388368, 0.0531519, 0.0677955, 0.08358, 0.0984831, 0.120445, 0.13221, 0.150472]
block_4 = [0.0282765, 0.0540716, 0.0755968, 0.0986637, 0.139235, 0.164178, 0.196091, 0.22674, 0.213301, 0.274244]
wait_free = [0.00908509, 0.0179934, 0.0279975, 0.0364352, 0.0549801, 0.0586574, 0.0831731, 0.0854588, 0.0931829, 0.164334]
stack = [0.00993995, 0.0201716, 0.0306056, 0.0423719, 0.0628235, 0.069747, 0.0986393, 0.0951225, 0.107656, 0.114378]
block = [0.0102734, 0.0196099, 0.0285342, 0.0391679, 0.050966, 0.0726303, 0.0756954, 0.0898179, 0.123732, 0.130098]
wait_free_2 = [0.0122593,0.0272755,0.0434581,0.0556638,0.0673139,0.0813106,0.0973055,0.120377,0.130954,0.150403]
stack_2 = [0.0158226,0.0281589,0.0440907,0.0641101,0.0865829,0.101809,0.122501,0.230217,0.159597,0.18888]
block_2 = [0.0325715,0.0704303,0.0919665,0.115982,0.226771,0.265361,0.330132,0.358651,0.417645,0.41126] 
# plt.plot(round, wait_free, c='red', label="wait-free queue no concurrence")
# plt.plot(round, stack, c='green',  label="treiber stack no concurrence")
plt.plot(round, block, c='blue',  label="block queue no concurrence")
# plt.plot(round, wait_free_2, c='red', linestyle='-.', label="wait-free queue 1 enqueue thread 1 dequeue thread")
# plt.plot(round, stack_2, c='green', linestyle='-.', label="treiber stack 1 enqueue thread 1 dequeue thread")
plt.plot(round, block_2, c='blue', linestyle='-.', label="block queue 1 enqueue thread 1 dequeue thread")
# plt.plot(round, wait_free_4, c='red', linestyle='--', label="wait-free queue 3 enqueue thread 1 dequeue thread")
# plt.plot(round, stack_4, c='green', linestyle='--', label="treiber stack 3 enqueue thread 1 dequeue thread")
plt.plot(round, block_4, c='blue', linestyle='--', label="block queue 3 enqueue thread 1 dequeue thread")

# plt.scatter(round, wait_free, c='red')
# plt.scatter(round, stack, c='green')
plt.scatter(round, block, c='blue')
# plt.scatter(round, wait_free_2, c='red')
# plt.scatter(round, stack_2, c='green')
plt.scatter(round, block_2, c='blue')
# plt.scatter(round, wait_free_4, c='red')
# plt.scatter(round, stack_4, c='green')
plt.scatter(round, block_4, c='blue')

plt.legend(loc='best')
# plt.yticks(range(0, 50, 5))
plt.grid(True, linestyle='--', alpha=0.5)
plt.xlabel("Round", fontdict={'size': 16})
plt.ylabel("Time(s)", fontdict={'size': 16})
plt.title("Time Comparison", fontdict={'size': 20})
plt.show()