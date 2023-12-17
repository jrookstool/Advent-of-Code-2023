const filePath = './day5_input.txt';

function handleFileInput(event) {
    const fileInput = event.target;
    const file = fileInput.files[0];

    if (file) {
        const reader = new FileReader();

        reader.onload = function (e) {
            const data = e.target.result;
            console.log(data);
            console.log("test");
        };

        reader.readAsText(file);
    }
}

const fileInput = document.getElementById('fileInput');
fileInput.addEventListener('change', handleFileInput);