import "./App.css";
import React, { useEffect, useState } from "react";
import { colors } from "./colors";
import LineChart from "./components/LineChart";
import { initializeApp } from "firebase/app";
import * as S from "./styles.js";

import {
  getFirestore,
  collection,
  getDocs,
  addDoc,
} from "firebase/firestore/lite";

const firebaseConfig = {};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);

const getData = async () => {
  const dados = collection(db, "dados");
  const dadosSnapshot = await getDocs(dados);
  const dadosList = dadosSnapshot.docs.map((doc) => doc.data());
  return dadosList;
};

function App() {
  const [time5, setTime5] = useState(0);
  const [time3, setTime3] = useState(0);
  const [time1, setTime1] = useState(0);
  const [name, setName] = useState("");
  const [actual, setActual] = useState(0);

  const [submited, setSubmited] = useState(false);
  const [initiated, setInitiated] = useState(false);
  const [charts, setCharts] = useState(false);
  const [colorsArray, setColorsArray] = useState([]);
  const [dataCharts, setDataCharts] = useState([]);

  const handleStart = () => {
    setActual(5);
    setTime5(performance.now());
    setInitiated(true);
    setColorsArray(colors.slice(0, 40));
  };

  const handleFinish5 = () => {
    setTime5(performance.now() - time5);
    setTime3(performance.now());
    setActual(3);
    setColorsArray(colors.slice(40, 64));
  };

  const handleFinish3 = () => {
    setTime3(performance.now() - time3);
    setTime1(performance.now());
    console.log("Iniciou  " + performance.now());
    setActual(1);
    setColorsArray(colors.slice(64, 72));
  };

  const handleFinish = () => {
    setTime1(performance.now() - time1);

    addDoc(collection(db, "dados"), {
      colors5: time5,
      colors3: time3,
      colors1: performance.now() - time1,
      name,
    })
      .then((data) => {
        setSubmited(true);
      })
      .catch((err) => {
        console.log(err);
      });
  };

  const handleSetChartsOn = () => {
    getData(db)
      .then((data) => {
        setDataCharts(data);
        setCharts(true);
      })
      .catch((err) => {
        console.log(err);
      });
  };

  const setHickHymanArray = (userTimes) => {
    const arrayHick = [];

    const rt = 155 * Math.log2(8 + 1);
    const rt2 = 155 * Math.log2(24 + 1);
    const rt3 = 155 * Math.log2(40 + 1);
    console.log(rt);
    console.log(rt2);
    console.log(rt3);
    console.log("MIAU");
  };

  return (
    <React.Fragment>
      {charts ? (
        <div className="charts-container">
          <div className="charts">
            {dataCharts.map((dataUser, id) => {
              const arrayTimeColorsTmp = [];
              arrayTimeColorsTmp.push(dataUser.colors1);
              arrayTimeColorsTmp.push(dataUser.colors3);
              arrayTimeColorsTmp.push(dataUser.colors5);
              setHickHymanArray(arrayTimeColorsTmp);
              // return (
              //   <LineChart
              //     key={id}
              //     name={dataUser.name}
              //     userTimes={arrayTimeColorsTmp}
              //     hickTimes={setHickHymanArray(arrayTimeColorsTmp)}
              //   />
              // );
            })}
          </div>
        </div>
      ) : (
        <div className="App">
          {submited ? (
            <div className="center">
              <S.Thanks>OBRIGADO!</S.Thanks>
            </div>
          ) : (
            <React.Fragment>
              {initiated ? (
                <div className="App">
                  {actual === 1 ? (
                    <React.Fragment>
                      <S.Description>MAIS UMA VEZ!!!</S.Description>
                      <div className="checkbox_class">
                        {colorsArray &&
                          colorsArray.map((color, id) => (
                            <S.Button
                              key={id}
                              type="submit"
                              onClick={handleFinish}
                              color={color}
                            />
                          ))}
                      </div>
                    </React.Fragment>
                  ) : actual === 5 ? (
                    <React.Fragment>
                      <S.Description>
                        SELECIONE A COR QUE VOCÊ MAIS GOSTOU!
                      </S.Description>
                      <div className="checkbox_class">
                        {colorsArray &&
                          colorsArray.map((color, id) => (
                            <S.Button
                              key={id}
                              type="submit"
                              onClick={handleFinish5}
                              color={color}
                            />
                          ))}
                      </div>
                    </React.Fragment>
                  ) : (
                    <React.Fragment>
                      <S.Description>
                        NOVAMENTE! SELECIONE A COR QUE VOCÊ MAIS GOSTOU!
                      </S.Description>
                      <div className="checkbox_class">
                        {colorsArray &&
                          colorsArray.map((color, id) => (
                            <S.Button
                              key={id}
                              type="submit"
                              onClick={handleFinish3}
                              color={color}
                            />
                          ))}
                      </div>
                    </React.Fragment>
                  )}
                </div>
              ) : (
                <div className="center">
                  <S.Label>Digite seu nome:</S.Label>
                  <S.Input
                    autoFocus
                    placeholder="Fulaninho de IHC"
                    type="text"
                    value={name}
                    onChange={(e) => setName(e.target.value)}
                  />

                  <S.InitButton color="#7CB9E8" onClick={handleStart}>
                    INICIAR
                  </S.InitButton>
                  <button
                    // style={{ display: "none" }}
                    onClick={handleSetChartsOn}
                  >
                    charts on
                  </button>
                </div>
              )}
            </React.Fragment>
          )}
        </div>
      )}
    </React.Fragment>
  );
}

export default App;
