import styled from "styled-components";

export const Button = styled.button`
  transition: 0.1s;
  background-color: ${(props) => props.color};
  width: 120px;
  height: 100px;
  color: #fff;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 10px;
  border: none;
  box-shadow: 1px 1px 1px black;

  &:hover {
    transform: scale(1.1);
  }
`;

export const Label = styled.span`
  color: #fff;
  font-size: 20px;
  margin-bottom: 5px;
  margin-right: 185px;
`;

export const Input = styled.input`
  font-size: 20px;
  border: none;
  border-radius: 8px;
  margin-bottom: 20px;
  width: 350px;
  height: 50px;
  text-align: center;
  background-color: #fff;

  &:focus {
    outline: none;
  }
`;

export const InitButton = styled.button`
  width: 355px;
  font-size: 25px;
  font-weight: 600;
  height: 60px;
  border: none;
  outline: none;
  background: #c38b8b;
  color: #fff;
  cursor: pointer;
  position: relative;
  z-index: 0;
  border-radius: 30px;
  letter-spacing: 2px;

  &::before {
    position: absolute;
    content: "";
    width: calc(100% + 4px);
    height: calc(100% + 4px);
    left: -2px;
    top: -2px;
    background: linear-gradient(
      124deg,
      #ff2400,
      #e81d1d,
      #e8b71d,
      #e3e81d,
      #1de840,
      #1ddde8,
      #2b1de8,
      #dd00f3,
      #dd00f3
    );
    background-size: 400%;
    z-index: -1;
    filter: blur(5px);
    animation: move 20s linear infinite;
    opacity: 0;
    transition: opacity 0.3s ease-in-out;
    border-radius: 10px;
  }

  &:hover::before {
    opacity: 1;
  }

  &::after {
    z-index: -1;
    content: "";
    position: absolute;
    width: 100%;
    height: 100%;
    background: #555273;
    left: 0;
    top: 0;
    border-radius: 10px;
  }

  @keyframes move {
    0% {
      background-position: 0 0;
    }
    50% {
      background-position: 400% 0;
    }
    100% {
      background-position: 0 0;
    }
  }
`;

export const Description = styled.div`
  color: #fff;
  font-weight: bold;
  font-size: 30px;
  margin: 50px 0;
`;

export const Thanks = styled.div`
  color: #fff;
  font-weight: bold;
  font-size: 50px;
  margin: 50px 0;
`;
