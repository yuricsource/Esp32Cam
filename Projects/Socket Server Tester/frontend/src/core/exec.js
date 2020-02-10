import store from "@/store";
const childProcess = window.require("child_process");

export function getPATH() {
  const shellPathCustom =
    store && store.state && store.state.shellPathCustom
      ? `:${store.state.shellPathCustom}`
      : "";

  return `${childProcess
    .execSync("echo $PATH")
    .toString()
    .replace(/\s/g, "")}:/usr/local/bin${shellPathCustom}`;
}

const PATH = getPATH();

function getSudoCommand(command, preCommand) {
  const c = `${!preCommand ? "" : `${preCommand} && `}/usr/bin/osascript -e 'do shell script "bash -c \\\"PATH=$PATH:${getPATH()} ${command.replace("sudo", "")}\\\"" with administrator privileges'`; // eslint-disable-line
  console.log("getSudoCommand", c);

  return c;
}

function run(command, { workingDirectory }) {
  // console.log("#### exec command run ", command, {
  //   env: { PATH: getPATH() },
  //   cwd: workingDirectory
  // });

  return new Promise((resolve, reject) => {
    childProcess.exec(
      command,
      { env: { PATH: getPATH() }, cwd: workingDirectory },
      (error, stdout) => {
        if (error) {
          return reject(error);
        }

        resolve(stdout);
      }
    );
  });
}

const runPipe = ({ command, pipe, workingDirectory }) => {
  const child = childProcess.exec(command, {
    env: { PATH },
    cwd: workingDirectory
  });

  child.stdout.on("data", data => {
    pipe({ data, type: "data" }); // TODO: change this to event based
  });

  child.stderr.on("data", data => {
    pipe({ data, type: "err" }); // TODO: change this to event based
  });

  child.on("close", code => {
    pipe({ data: `${code}`, type: "close" }); // TODO: change this to event based
  });

  return child;
};

export default function exec(command) {
  if (!command) {
    throw new Error("command is required");
  }

  let pipe;
  let workingDirectory;
  let preCommand;
  if (command instanceof Object && Object.keys(command).length > 0) {
    pipe = command.pipe;
    workingDirectory = command.workingDirectory;
    command = command.command;
    preCommand = command.preCommand;
  }

  const isRoot = process.getuid && process.getuid() === 0;
  const isSudo = command.indexOf("sudo") > -1;
  const runCommand =
    isSudo && !isRoot ? getSudoCommand(command, preCommand) : `${command}`;

  // console.log('#### exec command', runCommand);

  if (pipe) {
    return runPipe({
      command: runCommand,
      workingDirectory,
      preCommand,
      pipe
    });
  }

  return run(runCommand, { workingDirectory });
}

window.childProcess = childProcess;
