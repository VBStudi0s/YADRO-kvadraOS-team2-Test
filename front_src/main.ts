interface MemoryData {
    MemTotal: number;
    MemAvailable: number;
    SwapTotal: number;
    SwapFree: number;
}

interface CpuData {
    total_load: number;
    cores_load: number[];
}

interface SystemData {
    memory: MemoryData;
    cpu: CpuData;
}

const cpuTotalBar = document.getElementById('cpuTotalBar') as HTMLDivElement;
const cpuTotalText = document.getElementById('cpuTotalText') as HTMLSpanElement;
const coresContainer = document.getElementById('coresContainer') as HTMLDivElement;

const ramBar = document.getElementById('ramBar') as HTMLDivElement;
const ramText = document.getElementById('ramText') as HTMLSpanElement;
const swapBar = document.getElementById('swapBar') as HTMLDivElement;
const swapText = document.getElementById('swapText') as HTMLSpanElement;

function formatBytes(kb: number): string {
    if (kb < 1024) return `${kb} kB`;
    const mb = kb / 1024;
    if (mb < 1024) return `${mb.toFixed(1)} MB`;
    const gb = mb / 1024;
    return `${gb.toFixed(2)} GB`;
}

function renderCores(coresLoad: number[]) {
    const existingItems = coresContainer.children.length;
    const coresCount = coresLoad.length;

    // cores num changed (somehow)
    if (existingItems !== coresCount) {
        coresContainer.innerHTML = '';
        for (let i = 0; i < coresCount; i++) {
            const colDiv = document.createElement('div');
            colDiv.className = 'col-6 mb-2';
            colDiv.innerHTML = `
                <div class="d-flex justify-content-between small">
                    <span>Ядро ${i}</span>
                    <span id="coreText-${i}">0%</span>
                </div>
                <div class="progress" style="height: 20px;">
                    <div id="coreBar-${i}" class="progress-bar bg-info" role="progressbar" style="width: 0%;">0%</div>
                </div>
            `;
            coresContainer.appendChild(colDiv);
        }
    }

    for (let i = 0; i < coresCount; i++) {
        const load = coresLoad[i];
        const textSpan = document.getElementById(`coreText-${i}`);
        const barDiv = document.getElementById(`coreBar-${i}`);
        if (textSpan && barDiv) {
            const percent = load.toFixed(1);
            textSpan.textContent = `${percent}%`;
            barDiv.style.width = `${load}%`;
            barDiv.textContent = `${percent}%`;
        }
    }
}

function updateUI(jsonData: string): void {
    try {
        const data: SystemData = JSON.parse(jsonData);
        const mem = data.memory;
        const cpu = data.cpu;

        // CPU
        const totalLoad = cpu.total_load;
        cpuTotalBar.style.width = `${totalLoad}%`;
        cpuTotalBar.textContent = `${totalLoad.toFixed(1)}%`;
        cpuTotalText.textContent = `${totalLoad.toFixed(1)}%`;

        // Ядра
        if (cpu.cores_load && cpu.cores_load.length) {
            renderCores(cpu.cores_load);
        }

        // RAM
        const usedRam = mem.MemTotal - mem.MemAvailable;
        const ramPercent = (usedRam / mem.MemTotal) * 100;
        ramBar.style.width = `${ramPercent}%`;
        ramBar.textContent = `${ramPercent.toFixed(1)}%`;
        ramText.textContent = `${formatBytes(usedRam)} / ${formatBytes(mem.MemTotal)}`;

        // SWAP
        const usedSwap = mem.SwapTotal - mem.SwapFree;
        let swapPercent = 0;
        if (mem.SwapTotal > 0) {
            swapPercent = (usedSwap / mem.SwapTotal) * 100;
        }
        swapBar.style.width = `${swapPercent}%`;
        swapBar.textContent = `${swapPercent.toFixed(1)}%`;
        swapText.textContent = `${formatBytes(usedSwap)} / ${formatBytes(mem.SwapTotal)}`;

    } catch (e) {
        console.error('JSON parsing or UI update error:', e);
    }
};

window.addEventListener('load', () => {
    console.log('Frontend ready, waiting for data from backend...');
});

(window as any).updateUI = updateUI;
