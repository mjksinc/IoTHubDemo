$(document).ready(function () {
  var timeData = [],
    temperatureData = [],
      lightData = [],
        accelxData = [],
    accelyData = [];
     accelzData = [];
  var data = {
    labels: timeData,
    datasets: [
      {
        fill: false,
        label: 'Temperature',
        yAxisID: 'Temperature',
        borderColor: "rgba(255, 204, 0, 1)",
        pointBoarderColor: "rgba(255, 204, 0, 1)",
        backgroundColor: "rgba(255, 204, 0, 0.4)",
        pointHoverBackgroundColor: "rgba(255, 204, 0, 1)",
        pointHoverBorderColor: "rgba(255, 204, 0, 1)",
        data: temperatureData
      },
      {
          fill: false,
          label: 'Light',
          yAxisID: 'Light',
          borderColor: "rgba(240, 84, 84, 1)",
          pointBoarderColor: "rgba(240, 84, 84, 1)",
          backgroundColor: "rgba(240, 84, 84, 0.4)",
          pointHoverBackgroundColor: "rgba(240, 84, 84, 1)",
          pointHoverBorderColor: "rgba(240, 84, 84, 1)",
          data: lightData
        },
        {
            fill: false,
            label: 'Accel_x',
            yAxisID: 'Accel',
            borderColor: "rgba(24, 120, 240, 1)",
            pointBoarderColor: "rgba(24, 120, 240, 1)",
            backgroundColor: "rgba(24, 120, 240, 0.4)",
            pointHoverBackgroundColor: "rgba(24, 120, 240, 1)",
            pointHoverBorderColor: "rgba(24, 120, 240, 1)",
            data: accelxData
        },
        {
            fill: false,
            label: 'Accel_y',
            yAxisID: 'Accel',
            borderColor: "rgba(24, 80, 20, 1)",
            pointBoarderColor: "rgba(24, 80, 20, 1)",
            backgroundColor: "rgba(24, 80, 20, 0.4)",
            pointHoverBackgroundColor: "rgba(24, 80, 20, 1)",
            pointHoverBorderColor: "rgba(24, 80, 20, 1)",
            data: accelyData
        },
        {
            fill: false,
            label: 'Accel_z',
            yAxisID: 'Accel',
            borderColor: "rgba(24, 80, 130, 1)",
            pointBoarderColor: "rgba(24, 80, 130, 1)",
            backgroundColor: "rgba(24, 80, 130, 0.4)",
            pointHoverBackgroundColor: "rgba(24, 80, 130, 1)",
            pointHoverBorderColor: "rgba(24, 80, 130, 1)",
            data: accelzData
        }]
  }

  var basicOption = {
    title: {
      display: true,
      text: 'Temperature, Light & Acceleration Real-time Data',
      fontSize: 36
    },
    scales: {
      yAxes: [{
        id: 'Temperature',
        type: 'linear',
        scaleLabel: {
          labelString: 'Temperature(C)',
          display: true
        },
        position: 'left',
      }, {
          id: 'Light',
          type: 'linear',
          scaleLabel: {
            labelString: 'Lux',
            display: true
          },
          position: 'right'
          }, {
              id: 'Accel',
              type: 'linear',
              scaleLabel: {
                  labelString: 'Acceleration(m/s^2)',
                  display: true
              },
              position: 'right'
          }]
    }
  }

  //Get the context of the canvas element we want to select
  var ctx = document.getElementById("myChart").getContext("2d");
  var optionsNoAnimation = { animation: false }
  var myLineChart = new Chart(ctx, {
    type: 'line',
    data: data,
    options: basicOption
  });

  var ws = new WebSocket('wss://' + location.host);
  ws.onopen = function () {
    console.log('Successfully connect WebSocket');
  }
  ws.onmessage = function (message) {
    console.log('receive message' + message.data);
    try {
      var obj = JSON.parse(message.data);
      if(!obj.time || !obj.temperature) {
        return;
      }
      timeData.push(obj.time);
      temperatureData.push(obj.temperature);
      // only keep no more than 50 points in the line chart
      const maxLen = 50;
      var len = timeData.length;
      if (len > maxLen) {
        timeData.shift();
        temperatureData.shift();
      }

      if (obj.light) {
        lightData.push(obj.light);
      }
      if (lightData.length > maxLen) {
        lightData.shift();
    }

     if (obj.accelerometer_x) {
        accelxData.push(obj.accelerometer_x);
    }
    if (accelxData.length > maxLen) {
        accelxData.shift();
        }

        if (obj.accelerometer_y) {
            accelyData.push(obj.accelerometer_y);
        }
        if (accelyData.length > maxLen) {
            accelyData.shift();
        }

        if (obj.accelerometer_z) {
            accelzData.push(obj.accelerometer_z);
        }
        if (accelzData.length > maxLen) {
            accelzData.shift();
        }

      myLineChart.update();
    } catch (err) {
      console.error(err);
    }
  }
});
