<template>
  <div class="container d-flex flex-column flex-grow-1">
    <div class="table-responsive" id="general_table">
      <h3 class="p-3 text-center">Tüm Elemanlarınız Aşağıda Listelenmiştir</h3>
      <div class="d-flex justify-content-center">
        <div
          class="spinner-border"
          style="width: 3rem; height: 3rem"
          role="status"
          v-show="loading"
        >
          <span class="visually-hidden">Loading...</span>
        </div>
      </div>
      <table class="table table-dark table-striped" v-show="!loading">
        <thead>
          <tr>
            <th>Name</th>
            <th>Tel_no</th>
            <th>Email</th>
            <th>Adres</th>
            <th>Edit</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="employee in employees" :key="employee.uid">
            <td class="listElement">
              <p class="empText">{{ employee.name }}</p>
            </td>
            <td class="listElement">
              <p class="empText">{{ employee.phone }}</p>
            </td>
            <td class="listElement">
              <p class="empText">{{ employee.email }}</p>
            </td>
            <td class="listElement">
              <p class="empText">{{ employee.address }}</p>
            </td>
            <td class="listElement">
              <p class="empText"></p>
              <button
                id="edtbtn"
                class="btn btn-warning"
                @click="employeeToEdit = employee"
                data-bs-toggle="modal"
                data-bs-target="#editEmployee"
              >
                Edit
              </button>
              <button
                id="rmwbtn"
                class="btn btn-danger"
                @click="removeEmployee(employee)"
              >
                Remove
              </button>
            </td>
          </tr>
        </tbody>
      </table>
      <button
        id="addbtn"
        class="btn"
        data-bs-toggle="modal"
        data-bs-target="#addEmployee"
        v-show="!loading"
      >
        Add Employee
      </button>
    </div>
    <div
      class="modal fade"
      id="editEmployee"
      data-bs-backdrop="static"
      v-if="employeeToEdit != ''"
    >
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Eleman bilgilerini düzenle</h5>
            <button
              type="button"
              class="btn-close"
              data-bs-dismiss="modal"
              aria-label="Close"
              id="close-edit-btn"
            ></button>
          </div>
          <div class="modal-body">
            <EditEmployeeForm
              :employee="employeeToEdit"
              @closePopUp="closeEdit"
            />
          </div>
        </div>
      </div>
    </div>
    <div
      class="modal fade"
      id="addEmployee"
      tabindex="-1"
      data-bs-backdrop="static"
    >
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Eleman Ekle</h5>
            <button
              type="button"
              class="btn-close"
              data-bs-dismiss="modal"
              aria-label="Close"
              id="close-register-btn"
            ></button>
          </div>

          <div class="modal-body">
            <RegisterForm user_type="employee" @closePopUp="closeRegister" />
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { ref } from "@vue/reactivity";
import RegisterForm from "../components/RegisterForm.vue";
import EditEmployeeForm from "../components/EditEmployeeForm.vue";
import db from "../firebase";
import { functions } from "../firebase";
import { onBeforeMount } from "@vue/runtime-core";
export default {
  name: "EmployeeSettings",
  components: { RegisterForm, EditEmployeeForm },
  setup() {
    const userName = ref("");
    const telNo = ref("");
    const email = ref("");
    const adress = ref("");
    const password = ref("");
    const employeeToEdit = ref("");
    const employees = ref([]);
    const loading = ref(true);

    onBeforeMount(async () => {
      try {
        var empCol = await db.collection("employees").get();
        empCol.forEach(async (doc) => {
          var empId = doc.id;
          var getUser = functions.httpsCallable("getUser");

          var emp = await getUser({
            id: empId,
            collection: "employees",
          });
          employees.value.push(emp.data);
        });
        employees.value.sort(new Intl.Collator("de").compare);
        loading.value = false;
      } catch (err) {
        console.log(err.message);
      }
    });

    const refresh = () => {
      employees.value = [];
      db.collection("employees")
        .get()
        .then((snap) => {
          snap.forEach((doc) => {
            employees.value.push(doc.data());
          });
          employees.value.sort(new Intl.Collator("de").compare);
        });
    };

    const removeEmployee = async (e) => {
      console.log(e.uid);
      try {
        db.collection("employees").doc(e.uid).delete();
        var deleteUser = functions.httpsCallable("deleteUser");

        await deleteUser({
          uid: e.uid,
        });

        employees.value = [];
        var empCol = await db.collection("employees").get();
        empCol.forEach(async (doc) => {
          var empId = doc.id;
          try {
            var getUser = functions.httpsCallable("getUser");

            var emp = await getUser({
              id: empId,
              collection: "employees",
            });
            employees.value.push(emp.data);
          } catch (err) {
            console.log(err.message);
          }
        });
        employees.value.sort(new Intl.Collator("de").compare);
      } catch (err) {
        console.log(err.message);
      }
    };

    const closeRegister = () => {
      document.getElementById("close-register-btn").click();
    };

    const closeEdit = () => {
      document.getElementById("close-edit-btn").click();
      employeeToEdit.value = "";
    };

    /*if (employeeToEdit.value != "") {
      const editEmployee = document.getElementById("editEmployee");
      editEmployee.addEventListener("show.bs.modal", (e) => {
        console.log(e);
      });
    }*/

    return {
      userName,
      telNo,
      email,
      adress,
      password,
      employeeToEdit,
      employees,
      refresh,
      removeEmployee,
      closeRegister,
      closeEdit,
      loading,
    };
  },
};
</script>

<style scoped>
#general_table {
  margin: 2em;
}
table {
  min-height: 5vh;
  max-width: 100vw;
}
#addbtn {
  background: seagreen;
  max-width: 6em;
  min-width: 6em;
  border: 3px solid green;
  padding: 0em;
}
#rmwbtn {
  background: red;
  margin: 0.1em;
  max-width: 6em;
  min-width: 6em;
}
#edtbtn {
  background: orange;
  margin: 0.1em;
  max-width: 6em;
  min-width: 6em;
}
</style>
