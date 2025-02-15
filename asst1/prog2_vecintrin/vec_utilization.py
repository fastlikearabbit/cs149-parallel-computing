import matplotlib.pyplot as plt
from matplotlib.ticker import PercentFormatter

vector_widths = [2, 4, 8, 16]
utilization = [78.5, 71.5, 67.8, 66.0]

plt.figure(figsize=(8, 5))
bars = plt.bar(vector_widths, utilization, color='purple', alpha=0.7, edgecolor='black')

for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height,
             f'{height:.1f}%', ha='center', va='bottom')

plt.xlabel('Vector Width')
plt.ylabel('Utilization (%)')
plt.title('Vector Utilization vs. Vector Width')
plt.xticks(vector_widths)
plt.gca().yaxis.set_major_formatter(PercentFormatter()) 
plt.ylim(60, 80)
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.savefig('vector_utilization.png', dpi=300, bbox_inches='tight')
plt.show()
