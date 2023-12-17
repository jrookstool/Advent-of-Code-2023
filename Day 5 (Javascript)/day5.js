const filePath = './day5_input.txt';

function handleFileInput(event) {
    const fileInput = event.target;
    const file = fileInput.files[0];

    if (file) {
        const reader = new FileReader();

        reader.onload = function (e) {
            let lineNumber = 0;
            let found = false;
            const data = e.target.result;
            const lines = data.split('\r\n').filter(line => line.trim !== '');
            const seeds = lines[0].split(": ")[1];
            const seedsArray = seeds.split(" ");
            // for (let i = 0; i < seedsArray.length; i++) {
            //     seedsArray[i] = parseInt(seedsArray[i]);
            // }

            for (let i = 0; i < seedsArray.length; i += 2) {
                const currentValue = parseInt(seedsArray[i]);
                const additiveFactor = parseInt(seedsArray[i + 1]);
                for (let j = currentValue; j < currentValue + additiveFactor; j++) {
                    seedsArray.push(j);
                }
            }

            console.log(seedsArray);

            // Check seed-to-soil first
            lineNumber += 2;
            let seedRanges = [];
            let soilRanges = [];
            while (lines[lineNumber] !== "soil-to-fertilizer map:") {
                const values = lines[lineNumber].split(" ");
                seedRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                soilRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            console.log("seed ranges: " + seedRanges);
            console.log("soil ranges: " + soilRanges);

            let soils = [];
            for (let i = 0; i < seedsArray.length; i++) {
                for (let j = 0; j < seedRanges.length; j++) {
                    if (seedsArray[i] >= seedRanges[j][0] && seedsArray[i] <= seedRanges[j][1]) {
                        const soilIndex = seedsArray[i] - seedRanges[j][0] + soilRanges[j][0];
                        soils.push(soilIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push seed index to soil index.
                if (!found) soils.push(seedsArray[i]);
                found = false;
            }

            console.log(soils);

            // Check soil-to-fertilizer
            found = false;
            lineNumber++;
            soilRanges = [];
            let fertilizerRanges = [];
            while (lines[lineNumber] !== "fertilizer-to-water map:") {
                const values = lines[lineNumber].split(" ");
                soilRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                fertilizerRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let fertilizers = [];
            for (let i = 0; i < soils.length; i++) {
                for (let j = 0; j < soilRanges.length; j++) {
                    if (soils[i] >= soilRanges[j][0] && soils[i] <= soilRanges[j][1]) {
                        const fertilizerIndex = soils[i] - soilRanges[j][0] + fertilizerRanges[j][0];
                        fertilizers.push(fertilizerIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push soil index to fertilizer index.
                if (!found) fertilizers.push(soils[i]);
                found = false;
            }

            console.log(fertilizers);

            // Check fertilizer-to-water
            found = false;
            lineNumber++;
            fertilizerRanges = [];
            let waterRanges = [];
            while (lines[lineNumber] !== "water-to-light map:") {
                const values = lines[lineNumber].split(" ");
                fertilizerRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                waterRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let waters = [];
            for (let i = 0; i < fertilizers.length; i++) {
                for (let j = 0; j < fertilizerRanges.length; j++) {
                    if (fertilizers[i] >= fertilizerRanges[j][0] && fertilizers[i] <= fertilizerRanges[j][1]) {
                        const waterIndex = fertilizers[i] - fertilizerRanges[j][0] + waterRanges[j][0];
                        waters.push(waterIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push fertilizer index to water index.
                if (!found) waters.push(fertilizers[i]);
                found = false;
            }

            console.log(waters);

            // Check water-to-light
            found = false;
            lineNumber++;
            waterRanges = [];
            let lightRanges = [];
            while (lines[lineNumber] !== "light-to-temperature map:") {
                const values = lines[lineNumber].split(" ");
                waterRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                lightRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let lights = [];
            for (let i = 0; i < waters.length; i++) {
                for (let j = 0; j < waterRanges.length; j++) {
                    if (waters[i] >= waterRanges[j][0] && waters[i] <= waterRanges[j][1]) {
                        const lightIndex = waters[i] - waterRanges[j][0] + lightRanges[j][0];
                        lights.push(lightIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push water index to light index.
                if (!found) lights.push(waters[i]);
                found = false;
            }

            console.log(lights);

            // Check light-to-temperature
            found = false;
            lineNumber++;
            lightRanges = [];
            let temperatureRanges = [];
            while (lines[lineNumber] !== "temperature-to-humidity map:") {
                const values = lines[lineNumber].split(" ");
                lightRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                temperatureRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let temperatures = [];
            for (let i = 0; i < lights.length; i++) {
                for (let j = 0; j < lightRanges.length; j++) {
                    if (lights[i] >= lightRanges[j][0] && lights[i] <= lightRanges[j][1]) {
                        const temperatureIndex = lights[i] - lightRanges[j][0] + temperatureRanges[j][0];
                        temperatures.push(temperatureIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push light index to temperature index.
                if (!found) temperatures.push(lights[i]);
                found = false;
            }

            console.log(temperatures);

            // Check temperature-to-humidity
            found = false;
            lineNumber++;
            temperatureRanges = [];
            let humidityRanges = [];
            while (lines[lineNumber] !== "humidity-to-location map:") {
                const values = lines[lineNumber].split(" ");
                temperatureRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                humidityRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let humidities = [];
            for (let i = 0; i < temperatures.length; i++) {
                for (let j = 0; j < temperatureRanges.length; j++) {
                    if (temperatures[i] >= temperatureRanges[j][0] && temperatures[i] <= temperatureRanges[j][1]) {
                        const humidityIndex = temperatures[i] - temperatureRanges[j][0] + humidityRanges[j][0];
                        humidities.push(humidityIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push temperature index to humidity index.
                if (!found) humidities.push(temperatures[i]);
                found = false;
            }

            console.log(humidities);

            // Check humidity-to-location
            found = false;
            lineNumber++;
            humidityRanges = [];
            let locationRanges = [];
            while (lineNumber < lines.length) {
                const values = lines[lineNumber].split(" ");
                humidityRanges.push([parseInt(values[1]), parseInt(values[1]) + parseInt(values[2]) - 1]);
                locationRanges.push([parseInt(values[0]), parseInt(values[0]) + parseInt(values[2]) - 1]);
                lineNumber++;
            }

            let locations = [];
            for (let i = 0; i < humidities.length; i++) {
                for (let j = 0; j < humidityRanges.length; j++) {
                    if (humidities[i] >= humidityRanges[j][0] && humidities[i] <= humidityRanges[j][1]) {
                        const locationIndex = humidities[i] - humidityRanges[j][0] + locationRanges[j][0];
                        locations.push(locationIndex);
                        found = true;
                    }
                }    
                // If can't find one, just push humidity index to location index.
                if (!found) locations.push(humidities[i]);
                found = false;
            }

            console.log(locations);
        };

        reader.readAsText(file);
    }
}

function min(x) {
    let min = x[0];
    for (let i = 0; i < x.length; i++) {
        if (x[i] < min) {
            min = x[i];
        }
    }
}
const fileInput = document.getElementById('fileInput');
fileInput.addEventListener('change', handleFileInput);