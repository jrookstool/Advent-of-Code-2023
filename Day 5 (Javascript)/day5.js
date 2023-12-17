const filePath = './day5_input.txt';

function handleFileInput(event) {
    const fileInput = event.target;
    const file = fileInput.files[0];

    if (file) {
        const reader = new FileReader();

        reader.onload = function (e) {
            const data = e.target.result;
            const lines = data.split('\n');
            const seeds = lines[0].split(": ")[1];
            const seedsArray = seeds.split(" ");
            for (let i = 0; i < seedsArray.length; i++) {
                seedsArray[i] = parseInt(seedsArray[i]);
            }
            for (let i = 0; i < seedsArray.length; i++) {
                if (seedsArray[i] < 1263068588) {
                    console.log(seedsArray[i]);
                } 
            }
        };

        reader.readAsText(file);
    }
}

const fileInput = document.getElementById('fileInput');
fileInput.addEventListener('change', handleFileInput);