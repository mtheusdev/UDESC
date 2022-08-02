import React from "react";
import { Line } from "react-chartjs-2";
import { Chart as ChartJS, registerables } from "chart.js";

ChartJS.register(...registerables);

const LineChart = ({ name, userTimes, hickTimes }) => {
  console.log(name, userTimes);

  const data = {
    labels: [8, 24, 40],
    datasets: [
      {
        label: name,
        data: userTimes,
        fill: true,
        borderColor: "#742774",
      },
    ],
  };

  return (
    <div>
      <Line data={data} />
    </div>
  );
};

export default LineChart;
